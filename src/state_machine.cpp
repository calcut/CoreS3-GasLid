#include "state_machine.h"

StateMachine stateMachine;

void StateMachine::tunePID(void){
    compressorPID->SetTunings(envVars["compressorPID_P"],
                             envVars["compressorPID_I"],
                             envVars["compressorPID_D"]);
}

void StateMachine::init(void){
    Serial.println("Init state machine");

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

    Serial.println("Running state machine");

    inputs.pollSensorData();
    // inputs.pollPhysicalControls();
    // Serial.printf("Compressor PID input = %f\n", *compressorPIDinput);
    // Serial.printf("Compressor PID setpoint = %f\n", *compressorPIDsetpoint);
    // stateMachine.compressorPID->Compute();
    // Serial.printf("Compressor PID output = %f\n", compressorPIDoutput);

}


void StateMachine::sampleGasCards(){

    Serial.printf("Gas Card Sample Sequence starting...\n");

    for (int i = 0; i <= 3; i++){
        Serial.printf("Opening valves %d\n", i);
        outputs.setFlowValve(i, outputs.ValveState::OPEN);
        outputs.setReturnValve(i, outputs.ValveState::OPEN);
        
        Serial.printf("Running pump %d\n", i);
        outputs.setGasPumpSpeed(50);


        vTaskDelay(2000 / portTICK_PERIOD_MS);

        Serial.printf("Sampling gas cards now %d\n", i);
        //Actually do it here

        outputs.setGasPumpSpeed(0);
        Serial.printf("Closing valves %d\n", i);
        outputs.setFlowValve(i, outputs.ValveState::CLOSED);
        outputs.setReturnValve(i, outputs.ValveState::CLOSED);

        Serial.printf("Purging for 2s\n", i);
        outputs.setFlowValve(4, outputs.ValveState::OPEN);
        outputs.setReturnValve(4, outputs.ValveState::OPEN);
        outputs.setGasPumpSpeed(50);

        vTaskDelay(2000 / portTICK_PERIOD_MS);


        outputs.setGasPumpSpeed(0);
        outputs.setFlowValve(4, outputs.ValveState::CLOSED);
        outputs.setReturnValve(4, outputs.ValveState::CLOSED);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        Serial.printf("Purge Complete %d\n", i);
    }
}


