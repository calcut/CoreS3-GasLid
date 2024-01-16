#include "state_machine.h"

StateMachine stateMachine;

void StateMachine::tunePID(void){
    compressorPID->SetTunings(envVars["compressorPID_P"],
                             envVars["compressorPID_I"],
                             envVars["compressorPID_D"]);
}

void StateMachine::init(void){
    USBSerial.println("Init state machine");

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

    USBSerial.println("Running state machine");

    inputs.pollSensorData();
    // inputs.pollPhysicalControls();
    // USBSerial.printf("Compressor PID input = %f\n", *compressorPIDinput);
    // USBSerial.printf("Compressor PID setpoint = %f\n", *compressorPIDsetpoint);
    // stateMachine.compressorPID->Compute();
    // USBSerial.printf("Compressor PID output = %f\n", compressorPIDoutput);

}


void StateMachine::sampleGasCards(){

    USBSerial.printf("Gas Card Sample Sequence starting...\n");

    for (int i = 0; i <= 3; i++){
        USBSerial.printf("Opening valves %d\n", i);
        outputs.setFlowValve(i, outputs.ValveState::OPEN);
        outputs.setReturnValve(i, outputs.ValveState::OPEN);
        
        USBSerial.printf("Running pump %d\n", i);
        outputs.setGasPumpSpeed(50);


        vTaskDelay(2000 / portTICK_PERIOD_MS);

        USBSerial.printf("Sampling gas cards now %d\n", i);
        //Actually do it here

        outputs.setGasPumpSpeed(0);
        USBSerial.printf("Closing valves %d\n", i);
        outputs.setFlowValve(i, outputs.ValveState::CLOSED);
        outputs.setReturnValve(i, outputs.ValveState::CLOSED);

        USBSerial.printf("Purging for 2s\n", i);
        outputs.setFlowValve(4, outputs.ValveState::OPEN);
        outputs.setReturnValve(4, outputs.ValveState::OPEN);
        outputs.setGasPumpSpeed(50);

        vTaskDelay(2000 / portTICK_PERIOD_MS);


        outputs.setGasPumpSpeed(0);
        outputs.setFlowValve(4, outputs.ValveState::CLOSED);
        outputs.setReturnValve(4, outputs.ValveState::CLOSED);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        USBSerial.printf("Purge Complete %d\n", i);
    }
}


