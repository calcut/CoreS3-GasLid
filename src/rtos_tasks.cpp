#include "rtos_tasks.h"

SemaphoreHandle_t nc_mutex = xSemaphoreCreateMutex();
SemaphoreHandle_t modbus_mutex = xSemaphoreCreateMutex();

void setupRtos(void){

    // xTaskCreate(
    //     runStateMachine, // task function
    //     "State Machine", // task name
    //     16384, // stack size in bytes
    //     NULL, // pointer to parameters
    //     1, // priority
    //     NULL); // out pointer to task handle
    
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
    USBSerial.println("GUI setup complete");
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
    USBSerial.println("Failed to set callback for NotecardEnvVarManager.");
    }
    else{
        setDefaultEnvironment();
        USBSerial.println("NotecardManager started");
    }
    xSemaphoreGive(nc_mutex);

    while(1){

        if (notecardManager.serviceEnabled){
            USBSerial.printf("Notecard info service\n");
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
        USBSerial.printf("Notecard time sync\n");

        notecardManager.getTime();
        setRTC(notecardManager.epoch_time, notecardManager.utc_offset_minutes);
    }
    else{
        USBSerial.printf("Notecard not connected, skipping time sync\n");
    }
    USBSerial.printf("Notecard getEnvironment...\n");
    notecardManager.getEnvironment();
    USBSerial.printf("... Notecard getEnvironment done\n");

    USBSerial.printf("Notecard sendSensorData...\n");
    sendSensorData();
    USBSerial.printf("... Notecard sendSensorData done\n");

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
        USBSerial.printf("5 second debug print %d\n", millis());
        outputs.mod_inverter.init();
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

