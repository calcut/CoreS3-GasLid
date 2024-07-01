#include "state_machine.h"

StateMachine stateMachine;

void StateMachine::tunePID(void){
    gasPID->SetTunings(envVars["gasPID_P"],
                        envVars["gasPID_I"],
                        envVars["gasPID_D"]);
}

void StateMachine::init(void){
    ESP_LOGI("SM", "Init state machine");

    vTaskDelay(20 / portTICK_PERIOD_MS);

    gasPIDinput = &inputData.flowData["GasFlow"];
    gasPIDsetpoint = &envVars["GasFlowSetpoint"];

    gasPID = new QuickPID(
        gasPIDinput, // input
        &gasPIDoutput, // output
        gasPIDsetpoint, // setpoint
        envVars["gasPID_P"],
        envVars["gasPID_I"],
        envVars["gasPID_D"],
        QuickPID::Action::direct
    );
    // Dont enable PID yet because the input is not valid (nan)
    gasPID->SetOutputLimits(0, 70);

    initComplete = true;

}

void StateMachine::run(void){

    ESP_LOGD("SM", "Running state machine");

    inputs.pollSensorData();

    if (!gasSampleInProgress){
        inputs.pollGasSensors(0);
    }

    if(outputs.getJacketHeater()){
        ESP_LOGD("SM", "Jacket Heater is on");
        if(inputData.temperatureData["ts1"] > envVars["targetTempTank1"] 
                                    + envVars["jacketHeaterHysteresis"]){
            ESP_LOGD("SM", "Tank1 Heating Off");
            ESP_LOGD("SM", "ts1= %f, target= %f", inputData.temperatureData["ts1"], envVars["targetTempTank1"]);
            outputs.enableJacketHeater(false);
        }
    }
    else{
        ESP_LOGD("SM", "Jacket Heater is off");
        if(inputData.temperatureData["ts1"] < envVars["targetTempTank1"] 
                                - envVars["jacketHeaterHysteresis"]){
        ESP_LOGD("SM", "Tank1 Heating On");
        ESP_LOGD("SM", "ts1= %f, target= %f", inputData.temperatureData["ts1"], envVars["targetTempTank1"]);
        outputs.enableJacketHeater(true);
        }
    }
}

void StateMachine::gasTransferMode(){

    ESP_LOGI("SM", "Running Biofilter gas transfer cycle");
    ESP_LOGI("SM", "Opening valves flow 0 and return 3");
    outputs.setFlowValve(0, outputs.ValveState::OPEN);
    outputs.setReturnValve(3, outputs.ValveState::OPEN);

    //This is the extra valve to send the biofilter top gas back to ST1
    outputs.setTransferValve(outputs.ValveState::OPEN);
    gasPumpEnabled = true;
}

void StateMachine::sampleGasCards(){

    ESP_LOGI("SM", "Gas Card Sample Sequence starting...");

    if (gasSampleInProgress){
        ESP_LOGW("SM", "Gas sample already in progress, aborting");
        return;
    }

    gasSampleInProgress = true;
    gasPumpEnabled = true;

    int pumpTime_s = envVars["gasPumpTime_s"];
    int purgeTime_s = envVars["gasPurgeTime_s"];
    int sampleChannels = envVars["gasSampleChannels"];

    // If we got here from a manual sample request, reset the flag
    if (envVars["gasSampleNow"] == 1){
        envVars["gasSampleNow"] = 0;
    }

    //Stopping Gas Transfer cycle
    outputs.setFlowValve(0, outputs.ValveState::CLOSED);
    outputs.setReturnValve(3, outputs.ValveState::CLOSED);
    outputs.setTransferValve(outputs.ValveState::CLOSED);


    ESP_LOGI("SM", "Purging for %d seconds", purgeTime_s);
    outputs.setFlowValve(5, outputs.ValveState::OPEN);
    outputs.setReturnValve(5, outputs.ValveState::OPEN);

    vTaskDelay(purgeTime_s*1000 / portTICK_PERIOD_MS);

    outputs.setFlowValve(5, outputs.ValveState::CLOSED);
    outputs.setReturnValve(5, outputs.ValveState::CLOSED);


    for (int i = 0; i < sampleChannels; i++){


        // skip STINS2 and STINS3
        if (i == 1 || i == 2){
            inputData.gasData["gc2"] = nan("0");
            inputData.gasData["gc3"] = nan("0");
            continue;
        }

        ESP_LOGI("SM", "Opening valves %d", i);
        outputs.setFlowValve(i, outputs.ValveState::OPEN);
        outputs.setReturnValve(i, outputs.ValveState::OPEN);
        
        ESP_LOGI("SM", "Running pump for %d seconds", pumpTime_s);

        //Delay but check every second if it needs to stop sampling
        for (int j = 0; j < pumpTime_s; j++) {
            if (envVars["gasSampleStop"] == 1){
                stopSample();
            }
            inputs.pollGasSensors(0);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        ESP_LOGI("SM", "Sampling gas cards now %d", i);
        //Actually sample the gas cards here
        inputs.pollGasSensors(i+1);
        ESP_LOGI("SM", "Closing valves %d", i);
        outputs.setFlowValve(i, outputs.ValveState::CLOSED);
        outputs.setReturnValve(i, outputs.ValveState::CLOSED);

        ESP_LOGI("SM", "Purging for %d seconds", purgeTime_s);
        outputs.setFlowValve(5, outputs.ValveState::OPEN);
        outputs.setReturnValve(5, outputs.ValveState::OPEN);

        //Delay but check every second if it needs to stop sampling
        for (int j = 0; j < purgeTime_s; j++) {
            if (envVars["gasSampleStop"] == 1){
                stopSample();
            }
            inputs.pollGasSensors(0);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        outputs.setFlowValve(5, outputs.ValveState::CLOSED);
        outputs.setReturnValve(5, outputs.ValveState::CLOSED);


        ESP_LOGI("SM", "Purge Complete");

    }
    gasSampleInProgress = false;
    gasPumpEnabled = false;

}

void StateMachine::stopSample(){
    envVars["gasSampleStop"] = 0;
    gasSampleInProgress = false;
    gasPumpEnabled = false;
    ESP_LOGI("SM", "Stopping gas sample sequence and closing all valves");

    for (int i = 0; i < envVars["gasSampleChannels"]; i++){
        outputs.setFlowValve(i, outputs.ValveState::CLOSED);
        outputs.setReturnValve(i, outputs.ValveState::CLOSED);
    }
    outputs.setTransferValve(outputs.ValveState::CLOSED);
    
}

void StateMachine::computePID(){

    // If no gas flow ADC is available, use manual speed
    if (!inputs.err_gasflow_adc_enabled & gasPumpEnabled){
        ESP_LOGD("RTOS", "Gas flow ADC not available, using manual speed for gas pump");
        outputs.setGasPumpSpeed(envVars["GasPumpManualSpeed_pc"]);
        return;
    }
    //check if input is valid
    if(isnan(*gasPIDinput) & gasPumpEnabled){
        ESP_LOGW("RTOS", "Invalid PID input, gasPIDinput is nan, raising error");
        errorHandler(HAL_ERR_GASFLOW_ADC);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        return;
    }
    //Check if out of bounds
    float max = envVars["GasFlowMax"];
    float min = envVars["GasFlowMin"];
    if (*gasPIDinput > max){
        ESP_LOGW("RTOS", "PID Error, Gas flow too high");
        // gasPumpEnabled = false;
    }
    if (*gasPIDinput < min && gasPIDoutput > 40){
        ESP_LOGW("RTOS", "PID Error, Gas flow too low - connection failure?");
        // gasPumpEnabled = false;
    }

    if (gasPumpEnabled){
        gasPID->SetMode(QuickPID::Control::automatic);
        gasPID->Compute();
    }
    else{
        gasPID->SetMode(QuickPID::Control::manual);
        gasPIDoutput = 0;
    }
    // ESP_LOGD("RTOS", "KP=%f, KI=%f, KD=%f", gasPID->GetKp(), gasPID->GetKi(), gasPID->GetKd());
    // ESP_LOGD("RTOS", "PID input: %f", *gasPIDinput);
    // ESP_LOGD("RTOS", "PID setpoint: %f", *gasPIDsetpoint);
    // ESP_LOGD("RTOS", "PID output: %f", gasPIDoutput);
    outputs.setGasPumpSpeed(gasPIDoutput);
}

int StateMachine::getGasSampleDelay(void){

    // Get the current time
    time_t now;
    time(&now);
    struct tm *now_tm = localtime(&now);
    char logbuf1[80];
    char logbuf2[80];

    ESP_LOGD("SM", "Current time: %s", asctime(now_tm));

    // Define the three fixed times
    struct tm alarmTimes[4];
    for (int i = 0; i < 4; i++) {
        alarmTimes[i] = *now_tm; // copy current time structure
    }
    alarmTimes[0].tm_hour = envVars["sampleTime1_hour"];
    alarmTimes[0].tm_min = envVars["sampleTime1_min"];
    alarmTimes[0].tm_sec = 0;

    alarmTimes[1].tm_hour = envVars["sampleTime2_hour"];
    alarmTimes[1].tm_min = envVars["sampleTime2_min"];
    alarmTimes[1].tm_sec = 0;

    alarmTimes[2].tm_hour = envVars["sampleTime3_hour"];
    alarmTimes[2].tm_min = envVars["sampleTime3_min"];
    alarmTimes[2].tm_sec = 0;

    alarmTimes[3].tm_hour = envVars["sampleTime4_hour"];
    alarmTimes[3].tm_min = envVars["sampleTime4_min"];
    alarmTimes[3].tm_sec = 0;

    // Calculate the delay for the next run by finding the smallest delay to alarm
    uint32_t delay = UINT32_MAX;
    for (int i = 0; i < 4; i++) {
        time_t alarmTime = mktime(&alarmTimes[i]);
        if (alarmTime < now) {
            alarmTime += 24 * 60 * 60; // add 24 hours if the time has passed today
        }
        uint32_t diff = (alarmTime - now);
        strftime(logbuf1, sizeof(logbuf1), "%H:%M", localtime(&alarmTime));

        ESP_LOGD("SM", "Alarm time %d at %s in %d seconds", i, logbuf1, diff);
        if (diff < delay) {
            delay = diff;
            strftime(logbuf2, sizeof(logbuf2), "%H:%M", localtime(&alarmTime));
        }
    }
    ESP_LOGI("SM", "Next gas sample at %s (in %d seconds)", logbuf2, delay);
    return delay;
}