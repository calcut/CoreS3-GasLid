#include "notecard_context.h"

void myEnvVarCb(const char *key, const char *val, void *userCtx){

    // Assigns received environment variables to the appropriate
    // places. This requires an "unordered_map" of environment variables
    // to be defined in each class that needs to receive them.

    // The incoming type is converted to e.g. float or int as required
    // If the key is not found, it is ignored.

    ESP_LOGD("NCARD", "received: key=%s, val=%s", key, val);

    //If the first character of the key is "*", parse as a log level change
    if (key[0] == '*') {

        //drop the first character from the key
        key++;

        if (strcmp(val, "DEBUG") == 0) {
            ESP_LOGI("NCARD", "Setting %s log level to %s", key, val);
            esp_log_level_set(key, ESP_LOG_DEBUG);
            return;
        }
        if (strcmp(val, "INFO") == 0) {
            ESP_LOGI("NCARD", "Setting %s log level to %s", key, val);
            esp_log_level_set(key, ESP_LOG_INFO);
            return;
        }
        if (strcmp(val, "WARN") == 0) {
            ESP_LOGI("NCARD", "Setting %s log level to %s", key, val);
            esp_log_level_set(key, ESP_LOG_WARN);
            return;
        }
        if (strcmp(val, "ERROR") == 0) {
            ESP_LOGI("NCARD", "Setting %s log level to %s", key, val);
            esp_log_level_set(key, ESP_LOG_ERROR);
            return;
        }
    }

    if(strcmp(key, "clearEnvVar") == 0)
    {
        ESP_LOGI("NCARD", "Clearing environment variable: %s", val);
        notecardManager.deleteEnvironmentVar(val);
        notecardManager.newEnvVars = true;
        return;
    }

    try{
        stateMachine.envVars.at(key) = atof(val);
        ESP_LOGD("NCARD", "set stateMachine.envVars[\"%s\"]=%d",
                         key, stateMachine.envVars.at(key));
    } catch(std::out_of_range& e){}

    try{
        notecardManager.envVars.at(key) = atoi(val);
        ESP_LOGD("NCARD", "set notecardManager.envVars[\"%s\"]=%d",
                         key, notecardManager.envVars.at(key));
    } catch(std::out_of_range& e){}

    // A flag is set to indicate that new environment variables have been
    // received. This is used to trigger a call to refreshEnvironment()
    notecardManager.newEnvVars = true;
}

void sendBatchSensorData(){

    J *req = NoteNewRequest("note.add");

    // get unix timestamp from system time
    char timestr[12];
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int unixTime = tv.tv_sec;
    sprintf(timestr, "%d", unixTime);
    ESP_LOGD("NCARD", "Batch sensor data: %s", timestr); 

    J *body = JCreateObject();
    JAddFloatMapToObject(body, inputData.temperatureData);
    JAddFloatMapToObject(body, inputData.flowData);
    JAddNumberToObject(body, "Timestamp", unixTime);

    JAddStringToObject(req, "file", "inputs.qo");
    JAddBoolToObject(req, "sync", true);
    JAddItemToObject(req, "body", body);
    NoteRequest(req);

}

// void sendQueuedSensorData(void){
    // Could not get data queue to work
    // J* JSON objects appear to exist on the heap and do not persist
    // Which means you can't retrieve anything from a queue
// }


void sendSensorData(std::unordered_map<std::string, float> dataMap){

    // get unix timestamp from system time
    char timestr[12];
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int unixTime = tv.tv_sec;
    sprintf(timestr, "%d", unixTime);

    J *req = NoteNewRequest("note.add");

    JAddStringToObject(req, "file", "inputs.qo");
    JAddBoolToObject(req, "sync", true);

    J *body = JCreateObject();

    JAddFloatMapToObject(body, dataMap);
    JAddNumberToObject(body, "Timestamp", unixTime);
    JAddItemToObject(req, "body", body);
    NoteRequest(req);

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
    
void setDefaultEnvironment(void){

    // Copies the current value of the environment variables to the Notecard
    // and saves them as the default values.
    // Typically run once at startup.
    char value[12];
    char* key;
    int floatDecimals = 3;

    for (auto& envVar : notecardManager.envVars) {
        key = const_cast<char*>(envVar.first.c_str());
        dtostrf(envVar.second, 0, 0, value);
        notecardManager.setDefaultEnvironmentVar(key, value);
    }
    for (auto& envVar : stateMachine.envVars) {
        key = const_cast<char*>(envVar.first.c_str());
        dtostrf(envVar.second, 0, floatDecimals, value);
        notecardManager.setDefaultEnvironmentVar(key, value);
    }
}
