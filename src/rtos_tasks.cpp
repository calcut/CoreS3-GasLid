#include "rtos_tasks.h"

SemaphoreHandle_t nc_mutex = xSemaphoreCreateMutex();
SemaphoreHandle_t modbus_mutex = xSemaphoreCreateMutex();

SemaphoreHandle_t gasSampleSemaphore = xSemaphoreCreateBinary();
TimerHandle_t gasSampleTimer;

void setupRtos(void){

    esp_log_level_set("HAL", ESP_LOG_DEBUG);
    esp_log_level_set("RTOS", ESP_LOG_DEBUG);
    esp_log_level_set("SM", ESP_LOG_DEBUG);
    esp_log_level_set("IN", ESP_LOG_DEBUG);
    esp_log_level_set("OUT", ESP_LOG_DEBUG);
    esp_log_level_set("a1019", ESP_LOG_INFO);
    esp_log_level_set("NC-SIM", ESP_LOG_DEBUG);
    esp_log_level_set("NCARD", ESP_LOG_DEBUG);


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

    // xTaskCreate(
    //     readFlowMeters, // task function
    //     "Read Flow Meters", // task name
    //     16384, // stack size in bytes
    //     NULL, // pointer to parameters
    //     1, // priority
    //     NULL); // out pointer to task handle

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

    xSemaphoreTake(modbus_mutex, portMAX_DELAY);
    stateMachine.init();
    xSemaphoreGive(modbus_mutex);
    
    while(1){
        xSemaphoreTake(modbus_mutex, portMAX_DELAY);
        stateMachine.run();
        xSemaphoreGive(modbus_mutex);
        
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}



void computePID(void * pvParameters){
    while(1){
        
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void readFlowMeters(void *pvParameters)
{
    while (1)
    {
        inputs.serviceFlowMeters();
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

#ifdef USE_GUI
void serviceGUI(void * pvParameters){

    setupGui();
    Serial.println("GUI setup complete");
    while(1){
        int delay_ms = lv_timer_handler();
        vTaskDelay(delay_ms / portTICK_PERIOD_MS);
    }
}
#endif

#ifdef USE_NOTECARD
void serviceNotecard(void * pvParameters){

    xSemaphoreTake(nc_mutex, portMAX_DELAY);

    notecardManager.begin(serialDisplay);
    if (NotecardEnvVarManager_setEnvVarCb(notecardManager.envVarManager,
                             myEnvVarCb, NULL) != NEVM_SUCCESS)
    {
    Serial.println("Failed to set callback for NotecardEnvVarManager.");
    }
    else{
        setDefaultEnvironment();
        Serial.println("NotecardManager started");
    }
    xSemaphoreGive(nc_mutex);

    while(1){

        if (notecardManager.serviceEnabled){
            Serial.printf("Notecard info service\n");
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

            notecardManager.serviceTick = !notecardManager.serviceTick;
            xSemaphoreGive(nc_mutex);

            vTaskDelay(notecardManager.envVars["serviceInterval_s"]*1000 / portTICK_PERIOD_MS);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void timeSyncNotecard(void * pvParameters){
  while(1) {
    xSemaphoreTake(nc_mutex, portMAX_DELAY);
    notecardManager.cardStatus();

    if(notecardManager.connected){
        Serial.printf("Notecard time sync\n");

        notecardManager.getTime();
        setRTC(notecardManager.epoch_time, notecardManager.utc_offset_minutes);
    }
    else{
        Serial.printf("Notecard not connected, skipping time sync\n");
    }
    Serial.printf("Notecard getEnvironment...\n");
    notecardManager.getEnvironment();
    Serial.printf("... Notecard getEnvironment done\n");

    Serial.printf("Notecard sendSensorData...\n");
    sendSensorData();
    Serial.printf("... Notecard sendSensorData done\n");

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
            }

            // if the incoming string is complete, parse it:
            if (stringComplete) {
                ESP_LOGD("NC-SIM", "Received: %s", inputString.c_str());

                // Check if the input string contains the '=' character
                int equalIndex = inputString.indexOf('=');
                if (equalIndex != -1) {
                    ESP_LOGD("NC-SIM", "Parsing as envVar");

                    // Extract the key and value
                    String key_str = inputString.substring(0, equalIndex);
                    String value_str = inputString.substring(equalIndex + 1);

                    //convert the key and value to const char*
                    const char *key = key_str.c_str();
                    const char *value = value_str.c_str();

                    ESP_LOGD("NC-SIM","key=%s, value=%s\n", key, value);

                    myEnvVarCb(key, value, NULL);
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

        // ESP_LOGD("RTOS", "5 second debug print %d", millis());
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
#endif

void serviceGasCards(void * pvParameters){

    //Check if init has been run here?

    while(1){
        // Wait for the semaphore to be given
        xSemaphoreTake(gasSampleSemaphore, portMAX_DELAY);
        stateMachine.sampleGasCards();
    }
}

void gasSampleTimerCallback(TimerHandle_t xTimer) {
    // Give the semaphore to unblock the task
    xSemaphoreGive(gasSampleSemaphore);
}

void calculateNextAlarm() {

    // Stop and delete the current timer
    if (gasSampleTimer != NULL) {
        xTimerStop(gasSampleTimer, 0);
        xTimerDelete(gasSampleTimer, 0);
    }

    // Get the current time
    time_t now;
    time(&now);
    struct tm *now_tm = localtime(&now);
    char logbuf1[80];
    char logbuf2[80];

    ESP_LOGD("RTOS", "Current time: %s", asctime(now_tm));

    // Define the three fixed times
    struct tm alarmTimes[3];
    for (int i = 0; i < 3; i++) {
        alarmTimes[i] = *now_tm; // copy current time structure
    }
    alarmTimes[0].tm_hour = stateMachine.envVars["sampleTime1_hour"];
    alarmTimes[0].tm_min = stateMachine.envVars["sampleTime1_min"];
    alarmTimes[0].tm_sec = 0;

    alarmTimes[1].tm_hour = stateMachine.envVars["sampleTime2_hour"];
    alarmTimes[1].tm_min = stateMachine.envVars["sampleTime2_min"];
    alarmTimes[1].tm_sec = 0;

    alarmTimes[2].tm_hour = stateMachine.envVars["sampleTime3_hour"];
    alarmTimes[2].tm_min = stateMachine.envVars["sampleTime3_min"];
    alarmTimes[2].tm_sec = 0;

    // Calculate the delay for the next run by finding the smallest delay to alarm
    uint32_t delay = UINT32_MAX;
    for (int i = 0; i < 3; i++) {
        time_t alarmTime = mktime(&alarmTimes[i]);
        if (alarmTime < now) {
            alarmTime += 24 * 60 * 60; // add 24 hours if the time has passed today
        }
        uint32_t diff = (alarmTime - now) * 1000; // convert to milliseconds
        strftime(logbuf1, sizeof(logbuf1), "%H:%M", localtime(&alarmTime));

        ESP_LOGD("RTOS", "Alarm time %d at %s in %d seconds", i, logbuf1, diff/1000);
        if (diff < delay) {
            delay = diff;
            strftime(logbuf2, sizeof(logbuf2), "%H:%M", localtime(&alarmTime));
        }
    }
    ESP_LOGI("RTOS", "Next gas sample at %s (in %d seconds)", logbuf2, delay/1000);

    // Create and start the timer
    gasSampleTimer = xTimerCreate("gasSampleTimer", delay / portTICK_PERIOD_MS, pdFALSE, (void *)0, gasSampleTimerCallback);
    xTimerStart(gasSampleTimer, 0);
}
