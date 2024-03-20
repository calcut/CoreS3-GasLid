#include "rtos_tasks.h"

SemaphoreHandle_t nc_mutex = xSemaphoreCreateMutex();
SemaphoreHandle_t gasSampleSemaphore = xSemaphoreCreateBinary();
TimerHandle_t gasSampleTimer;

void setupRtos(void){

    esp_log_level_set("HAL", ESP_LOG_INFO);
    esp_log_level_set("RTOS", ESP_LOG_INFO);
    esp_log_level_set("SM", ESP_LOG_INFO);
    esp_log_level_set("IN", ESP_LOG_INFO);
    esp_log_level_set("OUT", ESP_LOG_INFO);
    esp_log_level_set("a1019", ESP_LOG_INFO);
    esp_log_level_set("NCARD", ESP_LOG_INFO);


    xTaskCreate(
        runStateMachine, // task function
        "State Machine", // task name
        16384, // stack size in bytes
        NULL, // pointer to parameters
        1, // priority
        NULL); // out pointer to task handle


    xTaskCreate(
        serviceGasCards, // task function
        "Service Gas Cards", // task name
        16384, // stack size in bytes
        NULL, // pointer to parameters
        1, // priority
        NULL); // out pointer to task handle

    xTaskCreate(
        serviceSerialInput, // task function
        "Service Serial Input", // task name
        16384, // stack size in bytes
        NULL, // pointer to parameters
        1, // priority
        NULL); // out pointer to task handle

    xTaskCreate(
        readFlowMeters, // task function
        "Read Flow Meters", // task name
        16384, // stack size in bytes
        NULL, // pointer to parameters
        1, // priority
        NULL); // out pointer to task handle

    xTaskCreate(
        servicePID, // task function
        "Compute PID", // task name
        16384, // stack size in bytes
        NULL, // pointer to parameters
        1, // priority
        NULL); // out pointer to task handle

#ifdef USE_NOTECARD
    xTaskCreate(
        serviceNotecard, // task function
        "Notecard Service", // task name
        16384, // stack size in bytes
        NULL, // pointer to parameters
        1, // priority
        NULL); // out pointer to task handle

    xTaskCreate(
        timeSyncNotecard, // task function
        "Notecard Time Sync", // task name
        16384, // stack size in bytes
        NULL, // pointer to parameters
        1, // priority
        NULL); // out pointer to task handle

    xTaskCreate(
        sendDataNotecard, // task function
        "Notecard Send Data", // task name
        16384, // stack size in bytes
        NULL, // pointer to parameters
        1, // priority
        NULL); // out pointer to task handle

    xTaskCreate(
        sampleDataNotecard, // task function
        "Notecard Sample Data", // task name
        16384, // stack size in bytes
        NULL, // pointer to parameters
        1, // priority
        NULL); // out pointer to task handle
#endif

#ifdef USE_GUI
    xTaskCreate(
        serviceGUI, // task function
        "LVGL GUI Service", // task name
        16384, // stack size in bytes
        NULL, // pointer to parameters
        1, // priority
        NULL); // out pointer to task handle
#endif

#ifdef DEBUG
    xTaskCreate(
        debugTask, // task function
        "Debug Task", // task name
        16384, // stack size in bytes
        NULL, // pointer to parameters
        1, // priority
        NULL); // out pointer to task handle
#endif
}

void runStateMachine(void * pvParameters){

    stateMachine.init();
    
    while(1){
        stateMachine.run();
        
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}



void servicePID(void * pvParameters){

    while (!stateMachine.initComplete){
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    while(1){
        stateMachine.computePID();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void readFlowMeters(void *pvParameters)
{
    while (1)
    {
        inputs.serviceFlowMeters();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

#ifdef USE_GUI
void serviceGUI(void * pvParameters){

    setupGui();
    ESP_LOGI("RTOS", "GUI setup complete");
    while(1){
        int delay_ms = lv_timer_handler();
        vTaskDelay(delay_ms / portTICK_PERIOD_MS);
    }
}
#endif

#ifdef USE_NOTECARD
void serviceNotecard(void * pvParameters){

    xSemaphoreTake(nc_mutex, portMAX_DELAY);

    notecardManager.begin();
    notecardManager.cardWirelessPenaltyReset();
    // notecardManager.clearWifiConnection();
    notecardManager.getWifiConnection();

    notecardManager.init(NC_UID, NC_MODE, NC_INBOUND, NC_OUTBOUND, NC_SYNC);
    
    if (NotecardEnvVarManager_setEnvVarCb(notecardManager.envVarManager,
                             myEnvVarCb, NULL) != NEVM_SUCCESS)
    {
    ESP_LOGE("RTOS", "Failed to set callback for NotecardEnvVarManager.");
    }
    else{
        setDefaultEnvironment();
        ESP_LOGI("RTOS", "NotecardManager started");
    }
    xSemaphoreGive(nc_mutex);

    while(1){

        if (notecardManager.serviceEnabled){
            ESP_LOGI("RTOS", "Notecard info service");
            xSemaphoreTake(nc_mutex, portMAX_DELAY);
            notecardManager.hubGet();
            vTaskDelay(10 / portTICK_PERIOD_MS);
            notecardManager.cardStatus();
            vTaskDelay(10 / portTICK_PERIOD_MS);
            notecardManager.getEnvironment();
            vTaskDelay(10 / portTICK_PERIOD_MS);
            notecardManager.hubStatus();
            vTaskDelay(10 / portTICK_PERIOD_MS);
            notecardManager.hubSyncStatus();
            vTaskDelay(10 / portTICK_PERIOD_MS);
            notecardManager.cardWireless();
            vTaskDelay(10 / portTICK_PERIOD_MS);

            refreshEnvironment();

            notecardManager.serviceTick = !notecardManager.serviceTick;
            xSemaphoreGive(nc_mutex);

            vTaskDelay(notecardManager.envVars["serviceInterval_s"]*1000 / portTICK_PERIOD_MS);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void sampleDataNotecard(void * pvParameters){
    while(1) {
    xSemaphoreTake(nc_mutex, portMAX_DELAY);
    ESP_LOGI("RTOS", "Notecard sampleSensorData...");
    queueBatchSensorData();


    xSemaphoreGive(nc_mutex);
    vTaskDelay(notecardManager.envVars["noteSampleInterval_s"]*1000 / portTICK_PERIOD_MS);
    }
}

void sendDataNotecard(void * pvParameters){
  while(1) {
    xSemaphoreTake(nc_mutex, portMAX_DELAY);


    ESP_LOGI("RTOS", "Notecard sendSensorData...");
    // queueSensorData(inputData.flowData);
    // ESP_LOGI("RTOS", "... Notecard sendSensorData done");
    notecardManager.sendQueuedSensorData();

    xSemaphoreGive(nc_mutex);
    vTaskDelay(notecardManager.envVars["noteSendInterval_s"]*1000 / portTICK_PERIOD_MS);
  }
}

void timeSyncNotecard(void * pvParameters){
  while(1) {
    xSemaphoreTake(nc_mutex, portMAX_DELAY);
    notecardManager.cardStatus();

    if(notecardManager.connected){
        notecardManager.getTime();
        setRTC(notecardManager.epoch_time, notecardManager.utc_offset_minutes);
    }
    else{
        ESP_LOGW("RTOS","Notecard not connected, skipping time sync");
    }

    //Need to regularly check for envVar updates.
    notecardManager.getEnvironment();
    refreshEnvironment();

    xSemaphoreGive(nc_mutex);
    vTaskDelay(notecardManager.envVars["timeSyncInterval_s"]*1000 / portTICK_PERIOD_MS);
  }
}
#endif

void serviceSerialInput(void * pvParameters){

    String inputString = ""; // a string to hold incoming data
    bool stringComplete = false; // whether the string is complete

    while(1){

        // if there's any serial available, read it:
        while (Serial.available()) {
            char inChar = (char)Serial.read();

            // if it's a newline, ignore it:
            if (inChar == '\n') {
                continue;
            } 
            // if it's a carriage return, mark complete:
            else if (inChar == '\r') {
                stringComplete = true;
            }
            // otherwise, add it to the input string:
            else {
                inputString += inChar;
                Serial.print(inChar);
            }

            // if the incoming string is complete, parse it:
            if (stringComplete) {
                ESP_LOGD("RTOS", "Received: %s", inputString.c_str());

                // Check if the input string contains the '=' character
                int equalIndex = inputString.indexOf('=');
                if (equalIndex != -1) {
                    ESP_LOGD("RTOS", "Parsing as envVar");

                    // Extract the key and value
                    String key_str = inputString.substring(0, equalIndex);
                    String value_str = inputString.substring(equalIndex + 1);

                    //convert the key and value to const char*
                    const char *key = key_str.c_str();
                    const char *value = value_str.c_str();

                    ESP_LOGD("RTOS","key=%s, value=%s", key, value);

                    // myEnvVarCb(key, value, NULL);
                    changeEnvVar(key, value);
                }

                // clear the string for new input:
                inputString = "";
                stringComplete = false;
            }

        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

#ifdef DEBUG
void debugTask(void * pvParameters){

    while(1){

        if (stateMachine.envVars["gasSampleNow"]){
            stateMachine.sampleGasCards();
            
            xSemaphoreTake(nc_mutex, portMAX_DELAY);
            notecardManager.sendSensorData(inputData.gasData);
            xSemaphoreGive(nc_mutex);
        }

        // ESP_LOGD("RTOS", "5 second debug print %d", millis());
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
#endif

void serviceGasCards(void * pvParameters){

    while (!stateMachine.initComplete){
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    while(1){
        // Wait for the semaphore to be given
        xSemaphoreTake(gasSampleSemaphore, portMAX_DELAY);
        stateMachine.sampleGasCards();

        xSemaphoreTake(nc_mutex, portMAX_DELAY);
        notecardManager.sendSensorData(inputData.gasData);
        xSemaphoreGive(nc_mutex);

    }
}

void gasSampleTimerCallback(TimerHandle_t xTimer) {
    // Give the semaphore to unblock the task
    xSemaphoreGive(gasSampleSemaphore);
}

void changeEnvVar(const char* key, const char* value){
    ESP_LOGI("RTOS", "Changing envVar %s to %s", key, value);

#ifdef USE_NOTECARD
    notecardManager.setEnvironmentVar(key, value);
    notecardManager.getEnvironment();
    // notecardManager.newEnvVars = true;  // shouldn't be needed
    refreshEnvironment();

#else
    //not properly tested yet
    float f = atof(value);
    stateMachine.envVars[key] = f;
    // myEnvVarCb(key, value, NULL); // might want this
#endif


}

void refreshEnvironment(void) {

    if (notecardManager.newEnvVars) {
        ESP_LOGI("RTOS", "Refreshing environment");

        // Stop and delete the current timer
        if (gasSampleTimer != NULL) {
            xTimerStop(gasSampleTimer, 0);
            xTimerDelete(gasSampleTimer, 0);
        }

        int delay = stateMachine.getGasSampleDelay();

        // Create and start the timer
        gasSampleTimer = xTimerCreate("gasSampleTimer", delay*1000 / portTICK_PERIOD_MS,
                                      pdFALSE, (void *)0, gasSampleTimerCallback);
        xTimerStart(gasSampleTimer, 0);

        //Refresh the PID tuning
        stateMachine.tunePID();

        //update the GUI
        display_refresh_envVars();

        notecardManager.newEnvVars = false;
    }
}
