#include "state_machine.h"

#define TAG "SM"

StateMachine stateMachine;

void StateMachine::tunePID(void){
    compressorPID->SetTunings(envVars["compressorPID_P"],
                             envVars["compressorPID_I"],
                             envVars["compressorPID_D"]);
}

void StateMachine::init(void){
    ESP_LOGI(TAG, "Init state machine");

    inputs.init();
    vTaskDelay(20 / portTICK_PERIOD_MS);
    outputs.init();

    // demandSensor = &inputs.temperatureData["Tw2_DHWFlow"];
    // defrostSensor = &inputs.temperatureData["Ta1_EvaporatorIn"];
    // flexStoreSensor = &inputs.temperatureData["Tw3_FlexStore"];
    // compressorPIDinput = &inputs.temperatureData["Tw2_DHWFlow"];
    // compressorPIDsetpoint = &envVars["demandThreshold"];
    // compressorPIDinput = &input;
    // compressorPIDsetpoint = &setpoint;

    // compressorPID = new QuickPID(
    //     compressorPIDinput, // input
    //     &compressorPIDoutput, // output
    //     compressorPIDsetpoint, // setpoint
    //     envVars["compressorPID_P"],
    //     envVars["compressorPID_I"],
    //     envVars["compressorPID_D"],
    //     QuickPID::Action::direct
    // );
    // // Dont enable PID yet because the input is not valid (nan)
    // // compressorPID->SetMode(QuickPID::Control::automatic);
    // compressorPID->SetOutputLimits(0, 100);
}

void StateMachine::run(void){

    ESP_LOGI(TAG, "Running state machine");

    inputs.pollSensorData();
    // inputs.pollPhysicalControls();
    // ESP_LOGI(TAG, "Compressor PID input = %f", *compressorPIDinput);
    // ESP_LOGI(TAG, "Compressor PID setpoint = %f", *compressorPIDsetpoint);
    // stateMachine.compressorPID->Compute();
    // ESP_LOGI(TAG, "Compressor PID output = %f", compressorPIDoutput);

}


void StateMachine::sampleGasCards(){

    ESP_LOGI(TAG, "Gas Card Sample Sequence starting...");

    int pumpTime_s = envVars["gasPumpTime_s"];
    int purgeTime_s = envVars["gasPurgeTime_s"];
    int pumpSpeed_pc = envVars["gasPumpSpeed_pc"];
    int sampleChannels = envVars["gasSampleChannels"];


    for (int i = 0; i < sampleChannels; i++){
        ESP_LOGI(TAG, "Opening valves %d", i);
        outputs.setFlowValve(i, outputs.ValveState::OPEN);
        outputs.setReturnValve(i, outputs.ValveState::OPEN);
        
        ESP_LOGI(TAG, "Running pump at %d%% for %d seconds", pumpSpeed_pc, pumpTime_s);
        outputs.setGasPumpSpeed(pumpSpeed_pc);
        vTaskDelay(pumpTime_s*1000 / portTICK_PERIOD_MS);

        ESP_LOGI(TAG, "Sampling gas cards now %d", i);
        //Actually do it here

        outputs.setGasPumpSpeed(0);
        ESP_LOGI(TAG, "Closing valves %d", i);
        outputs.setFlowValve(i, outputs.ValveState::CLOSED);
        outputs.setReturnValve(i, outputs.ValveState::CLOSED);

        ESP_LOGI(TAG, "Purging at %d%% for %d seconds", pumpSpeed_pc, purgeTime_s);
        outputs.setFlowValve(4, outputs.ValveState::OPEN);
        outputs.setReturnValve(4, outputs.ValveState::OPEN);
        outputs.setGasPumpSpeed(pumpSpeed_pc);
        vTaskDelay(purgeTime_s*1000 / portTICK_PERIOD_MS);
        outputs.setGasPumpSpeed(0);
        outputs.setFlowValve(4, outputs.ValveState::CLOSED);
        outputs.setReturnValve(4, outputs.ValveState::CLOSED);

        ESP_LOGI(TAG, "Purge Complete");
    }
}



