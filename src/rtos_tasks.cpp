#include "rtos_tasks.h"

SemaphoreHandle_t nc_mutex = xSemaphoreCreateMutex();
SemaphoreHandle_t modbus_mutex = xSemaphoreCreateMutex();

void setupRtos(void){

    esp_log_level_set("HAL", ESP_LOG_DEBUG);
    esp_log_level_set("RTOS", ESP_LOG_DEBUG);
    esp_log_level_set("SM", ESP_LOG_DEBUG);
    esp_log_level_set("IN", ESP_LOG_DEBUG);
    esp_log_level_set("OUT", ESP_LOG_DEBUG);
    esp_log_level_set("a1019", ESP_LOG_INFO);

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
    inputs.initFlowMeters(PIN_PULSE_COUNT);   
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

#ifdef DEBUG
void debugTask(void * pvParameters){

    // outputs.init();
    while(1){
        // if (db_vars.enabled == true){
        //     compressorPID->Compute();
        //     set_compressor_speed(qo_vars.compressor_target_speed);
        // }
        ESP_LOGD("RTOS", "5 second debug print %d", millis());
        // bool relays[16];
        // outputs.mod_16RO.getRelays(relays);
        // // relays[0] = !relays[0];
        // // relays[1] = !relays[1];
        // relays[15] = !relays[15];
        // outputs.mod_16RO.setRelays(relays);
        // OutputType voltagetype = OutputType::VOLTAGE;
        // outputs.mod_8AO.setWatchdog(10000);
        // outputs.setCompressorSpeed(50);

        // xSemaphoreTake(modbus_mutex, portMAX_DELAY);
        // inputs.mod_a1019.init();
        // xSemaphoreGive(modbus_mutex);

        vTaskDelay(5000 / portTICK_PERIOD_MS);
        
    }
}
#endif

void serviceGasCards(void * pvParameters){

    //Check if init has been run here?

    while(1){
        // vTaskDelay(calculateNextDelay() / portTICK_PERIOD_MS);
        vTaskDelay(10000 / portTICK_PERIOD_MS);
        stateMachine.sampleGasCards();
    }
}

uint32_t calculateNextDelay() {
    // Get the current time
    time_t now;
    time(&now);
    struct tm *now_tm = localtime(&now);

    Serial.printf("Current time: %s", asctime(now_tm));

    // Define the three fixed times
    struct tm fixedTimes[3];
    for (int i = 0; i < 3; i++) {
        fixedTimes[i] = *now_tm; // copy current time structure
    }
    fixedTimes[0].tm_hour = 8;  fixedTimes[0].tm_min = 0;  fixedTimes[0].tm_sec = 0;
    fixedTimes[1].tm_hour = 14; fixedTimes[1].tm_min = 0;  fixedTimes[1].tm_sec = 0;
    fixedTimes[2].tm_hour = 20; fixedTimes[2].tm_min = 0;  fixedTimes[2].tm_sec = 0;

    // Calculate the delay for the next run
    uint32_t delay = UINT32_MAX;
    for (int i = 0; i < 3; i++) {
        time_t fixedTime = mktime(&fixedTimes[i]);
        if (fixedTime < now) {
            fixedTime += 24 * 60 * 60; // add 24 hours if the time has passed today
        }
        uint32_t diff = (fixedTime - now) * 1000; // convert to milliseconds
        Serial.printf("Fixed time %d in %d seconds\n", i, diff / 1000);
        if (diff < delay) {
            delay = diff;
        }
    }

    Serial.printf("Next run in %d seconds\n", delay / 1000);
    return delay / portTICK_PERIOD_MS; // convert to ticks
}
