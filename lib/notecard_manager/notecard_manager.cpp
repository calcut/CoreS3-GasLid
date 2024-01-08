#include "notecard_manager.h"

NotecardManager notecardManager;


NotecardManager::NotecardManager(){}

void NotecardManager::begin(Stream &serial_stream){
    notecard.begin(NOTE_I2C_ADDR_DEFAULT, NOTE_I2C_MAX_DEFAULT, Wire);
    notecard.setDebugOutputStream(serial_stream);

    envVarManager = NotecardEnvVarManager_alloc();
    if (envVarManager == NULL) {
        // Handle failed allocation.
        USBSerial.println("Failed to allocate NotecardEnvVarManager.");
    }
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
            notecard.logDebug("FATAL: Failed to configure Notecard!\n");
            USBSerial.println("FATAL: Failed to configure Notecard!");
            while(1);
        }
    }

    req = notecard.newRequest("card.aux");
    if (req) {
        JAddStringToObject(req, "mode", "off");
        if (!notecard.sendRequest(req)) {
            notecard.logDebug("Warning, failed to set card.aux mode=off\n");
        }
    }

    req = notecard.newRequest("card.dfu");
    if (req) {
        JAddStringToObject(req, "name", "esp32");
        JAddBoolToObject(req, "on", DFU_ENABLE);
        if (!notecard.sendRequest(req)) {
            notecard.logDebug("Warning, failed to enable outboard DFU\n");
        }
    }
}

void NotecardManager::hubGet(){
    if (J *req = notecard.newRequest("hub.get")) {
        J *rsp = notecard.requestAndResponse(req);
        char *tempDevice = JGetString(rsp, "device");
        strlcpy(deviceUID, tempDevice, sizeof(deviceUID));
        char *tempSN = JGetString(rsp, "sn");
        strlcpy(sn, tempSN, sizeof(sn));
        notecard.deleteResponse(rsp);
    }
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
        USBSerial.printf("modified time: %d\n", env_modified_time);
        notecard.deleteResponse(rsp);

        notecard.logDebug("Fetching environment variables...\n");
        if (NotecardEnvVarManager_fetch(envVarManager, NULL, NEVM_ENV_VAR_ALL)
                != NEVM_SUCCESS) {
                USBSerial.println("NotecardEnvVarManager_fetch failed.");
            }
    }   
}   

void NotecardManager::setEnvironmentVar(char *name, char * text){
    J *req = notecard.newRequest("env.set");
    JAddStringToObject(req, "name", name);
    JAddStringToObject(req, "text", text);
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

void NotecardManager::setDefaultEnvironmentVar(char *name, char *text){
    J *req = notecard.newRequest("env.default");
    JAddStringToObject(req, "name", name);
    JAddStringToObject(req, "text", text);
    notecard.sendRequest(req);
}