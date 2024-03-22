#include "notecard_manager.h"


NotecardManager notecardManager;
SerialDebug serialDebug;


NotecardManager::NotecardManager(){}

void NotecardManager::begin(){
    notecard.begin(NOTE_I2C_ADDR_DEFAULT, NOTE_I2C_MAX_DEFAULT, Wire);
    notecard.setDebugOutputStream(serialDebug);
    // notecard.setDebugOutputStream(Serial);

    envVarManager = NotecardEnvVarManager_alloc();
    if (envVarManager == NULL) {
        // Handle failed allocation.
        ESP_LOGE("NCARD", "Failed to allocate NotecardEnvVarManager.");
    }

    err = hubGet();
    if(err != ESP_OK){
        ESP_LOGE("NCARD", "Failed to communicate with notecard");
    }

    configureOutboardDFU();

    queue = JCreateObject();

}

void NotecardManager::getWifiConnection(){

    J *req = NoteNewRequest("card.wifi");

    if (J *rsp = NoteRequestResponse(req))
    {
        if(NoteResponseError(rsp)){
            ESP_LOGE("NCARD", "Failed to get wifi credentials - likely not a Wifi Notecard.");
            return;
        }

        char *ssid = JGetString(rsp, "ssid");
        NoteDeleteResponse(rsp);


        if(strcmp(ssid, "") == 0){
            ESP_LOGI("NCARD", "No wifi credentials found. Starting SoftAP");
            softAP();
        }
        else{
            ESP_LOGI("NCARD", "Wifi credentials found");
            ESP_LOGI("NCARD", "Current SSID: %s", ssid);
        }
    }
}

void NotecardManager::clearWifiConnection(){
    J *req = NoteNewRequest("card.wifi");
    JAddStringToObject(req, "ssid", "-");
    JAddStringToObject(req, "password", "-");

    NoteRequest(req);
    ESP_LOGI("NCARD", "Cleared Wifi Credentials");
}

void NotecardManager::softAP(){
    J *req = NoteNewRequest("card.wifi");
    JAddStringToObject(req, "name", "Notecard-");
    JAddBoolToObject(req, "start", true);
    // JAddStringToObject(req, "org", "ACME Inc");

    NoteRequest(req);
    ESP_LOGI("NCARD", "SoftAP enabled");
}


void NotecardManager::init(const char *uid, const char *mode, int inbound, int outbound, bool sync){

    J *req = notecard.newRequest("hub.set");
    if (req) {
        JAddStringToObject(req, "product", uid);
        JAddStringToObject(req, "mode", mode);
        JAddNumberToObject(req, "inbound", inbound);
        JAddNumberToObject(req, "outbound", outbound);
        JAddBoolToObject(req, "sync", true);
        JAddBoolToObject(req, "align", true); // Align periodic syncs to UTC intervals

        if (!notecard.sendRequest(req)) {
            ESP_LOGE("NCARD", "Failed to configure Notecard!");
            while(1);
        }
    }
}

void NotecardManager::configureOutboardDFU(){

    J *req = notecard.newRequest("card.aux");
    if (req) {
        JAddStringToObject(req, "mode", "off");
        if (!notecard.sendRequest(req)) {
            ESP_LOGE("NCARD", "failed to set card.aux mode=off");
        }
    }

    req = notecard.newRequest("dfu.status");
    if (req) {
        JAddBoolToObject(req, "on", DFU_ENABLE);
        JAddStringToObject(req, "version", AUTO_VERSION);
        if (!notecard.sendRequest(req)) {
            ESP_LOGE("NCARD", "failed to set dfu.status on=true version=0.0.1");
        }
    }

    req = notecard.newRequest("card.dfu");
    if (req) {
        JAddStringToObject(req, "name", "esp32");
        JAddBoolToObject(req, "on", DFU_ENABLE);
        ESP_LOGW("NCARD", "card.dfu esp32 mode %s", DFU_ENABLE ? "enabled" : "disabled");
        if (!notecard.sendRequest(req)) {
            ESP_LOGE("NCARD", "failed to enable outboard DFU");
        }
    }
}

esp_err_t NotecardManager::hubGet(){
    if (J *req = notecard.newRequest("hub.get")) {
        J *rsp = notecard.requestAndResponse(req);
        char *tempDevice = JGetString(rsp, "device");
        strlcpy(deviceUID, tempDevice, sizeof(deviceUID));
        char *tempSN = JGetString(rsp, "sn");
        strlcpy(sn, tempSN, sizeof(sn));
        notecard.deleteResponse(rsp);
        return ESP_OK;
    } else return ESP_FAIL;
}

void NotecardManager::hubStatus(){
    if (J *req = notecard.newRequest("hub.status")) {
        J *rsp = notecard.requestAndResponse(req);

        char *tempStatus = JGetString(rsp, "status");
        strlcpy(hub_status, tempStatus, sizeof(hub_status));
        notecard.deleteResponse(rsp);
    }
}
void NotecardManager::hubSyncStatus(){
    if (J *req = notecard.newRequest("hub.sync.status")) {
        J *rsp = notecard.requestAndResponse(req);
        char *tempStatus = JGetString(rsp, "status");
        strlcpy(hub_sync_status, tempStatus, sizeof(hub_sync_status));
        notecard.deleteResponse(rsp);
    }
}

void NotecardManager::cardStatus(){
    char status[20];
    if (J *req = notecard.newRequest("card.status")) {
        J *rsp = notecard.requestAndResponse(req);

        connected = JGetBool(rsp, "connected");
        char *tempStatus = JGetString(rsp, "status");
        strlcpy(status, tempStatus, sizeof(status));
        int storage = JGetInt(rsp, "storage");
        int time = JGetInt(rsp, "time");
        bool cell = JGetBool(rsp, "cell");
        notecard.deleteResponse(rsp);
    }
}
void NotecardManager::cardWireless(){
    if (J *req = notecard.newRequest("card.wireless")) {
        J *rsp = notecard.requestAndResponse(req);
        J *net = JGetObject(rsp, "net");
        bars = JGetInt(net, "bars");
        rssi = JGetInt(net, "rssi");
        char *tempRat = JGetString(net, "rat");
        char *tempBand = JGetString(net, "band");
        strlcpy(rat, tempRat, sizeof(rat));
        strlcpy(band, tempBand, sizeof(band));
    }
}

void NotecardManager::cardWirelessPenaltyReset(){
    if (J *req = notecard.newRequest("card.wireless.penalty")) {
        JAddBoolToObject(req, "reset", true);
        J *rsp = notecard.requestAndResponse(req);
        notecard.deleteResponse(rsp);
    }
}

void NotecardManager::getEnvironment(){

    // Check if any environment variables have been modified.
    J *req = notecard.newRequest("env.modified");
    JAddNumberToObject(req, "time", env_modified_time);
    J *rsp = notecard.requestAndResponse(req);

    if (notecard.responseError(rsp)){
        //No modification
        notecard.deleteResponse(rsp);
    }

    // Update the environment variable manager if there have been modifications.
    else {
        notecard.logDebug(JConvertToJSONString(rsp));
        env_modified_time = JGetInt(rsp, "time");
        ESP_LOGD("NCARD", "Env modified time: %d", env_modified_time);
        notecard.deleteResponse(rsp);

        ESP_LOGD("NCARD","Fetching environment variables...");
        if (NotecardEnvVarManager_fetch(envVarManager, NULL, NEVM_ENV_VAR_ALL)
                != NEVM_SUCCESS) {
                ESP_LOGE("NCARD", "NotecardEnvVarManager_fetch failed.");
            }
    }   
}   

void NotecardManager::setEnvironmentVar(const char *name, const char *text){
    J *req = notecard.newRequest("env.set");
    JAddStringToObject(req, "name", name);
    JAddStringToObject(req, "text", text);
    notecard.sendRequest(req);
}

void NotecardManager::deleteEnvironmentVar(const char *name){
    J *req = notecard.newRequest("env.set");
    JAddStringToObject(req, "name", name);
    notecard.sendRequest(req);
}

void NotecardManager::getTime(){
    if (J *req = notecard.newRequest("card.time")) {
        J *rsp = notecard.requestAndResponse(req);
        epoch_time = JGetInt(rsp, "time");
        utc_offset_minutes = JGetInt(rsp, "minutes");
        notecard.deleteResponse(rsp);
    }
}

void NotecardManager::setDefaultEnvironmentVar(const char *name, const char *text){
    J *req = notecard.newRequest("env.default");
    JAddStringToObject(req, "name", name);
    JAddStringToObject(req, "text", text);
    notecard.sendRequest(req);
}

void NotecardManager::sendSensorData(std::unordered_map<std::string, float> dataMap){

    // get unix timestamp from system time
    char timestr[12];
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int unixTime = tv.tv_sec;
    sprintf(timestr, "%d", unixTime);

    J *req = NoteNewRequest("note.add");

    JAddStringToObject(req, "file", NC_NOTEFILE);
    JAddBoolToObject(req, "sync", true);

    J *body = JCreateObject();

    JAddFloatMapToObject(body, dataMap);
    JAddNumberToObject(body, "Timestamp", unixTime);
    JAddItemToObject(req, "body", body);
    NoteRequest(req);
}

void NotecardManager::appendToQueue(std::unordered_map<std::string, float> floatMap){

    // get unix timestamp from system time
    char timestr[12];
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int unixTime = tv.tv_sec;
    sprintf(timestr, "%d", unixTime);
    ESP_LOGD("NCARD", "appendToQueue: %s", timestr); 

    J *entry = JCreateObject();
    JAddFloatMapToObject(entry, floatMap);
    JAddItemToObject(queue, timestr, entry);

}

void NotecardManager::sendQueuedSensorData(void){
    
    char *queueStr = JConvertToJSONString(notecardManager.queue);

    if (queueStr == NULL) {
        ESP_LOGW("NCARD", "Error converting queue to JSONString");
    }
    else {
        ESP_LOGI("NCARD", "Sending Queue: %s\n", queueStr);
    }

    // J *body = JCreateObject();
    J *req = NoteNewRequest("note.add");
    JAddBoolToObject(req, "sync", true);
    JAddStringToObject(req, "file", NC_NOTEFILE);
    JAddItemToObject(req, "body", notecardManager.queue);

    notecardManager.queue = JCreateObject();
    NoteRequest(req);
}

size_t SerialDebug::write(const uint8_t *buffer, size_t size){

    //Intended to intercept log messages from the notecard and translate them to ESP_LOGx messages
    //Append the buffer to the tempBuffer

    // if the tempBuffer will overflow, then print the current contents and reset the buffer
    if(tempBufferIndex + size >= sizeof(tempBuffer)){
        ESP_LOGD("NCARD", "Following log message is truncated");
        size = sizeof(tempBuffer) - tempBufferIndex;
        memcpy(&tempBuffer[tempBufferIndex], buffer, size);
        ESP_LOGD("NCARD", "[Truncated] %s", tempBuffer);
        tempBufferIndex = 0;
    }
    else{
        memcpy(&tempBuffer[tempBufferIndex], buffer, size);
        tempBufferIndex += size;

        //if tempbuffer ends in a newline, then send it to the ESP_LOGD hander
        if (tempBuffer[tempBufferIndex-1] == '\n'){
            tempBuffer[tempBufferIndex-1] = '\0';
            ESP_LOGD("NCARD", "%s", tempBuffer);
            tempBufferIndex = 0;
        }
    }

    return size;
}

void JAddFloatMapToObject(J *obj, std::unordered_map<std::string, float> map){

    for (auto& keyval : map) {
        if (!isnan(keyval.second)) {
            char buffer[12];
            dtostrf(keyval.second, 0, 2, buffer);
            JAddStringToObject(obj,
                const_cast<char*>(keyval.first.c_str()),
                buffer);
        }
    }
}   