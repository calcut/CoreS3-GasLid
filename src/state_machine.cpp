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
    previousState = currentState;

    inputs.pollSensorData();
    // inputs.pollPhysicalControls();
    // USBSerial.printf("Compressor PID input = %f\n", *compressorPIDinput);
    // USBSerial.printf("Compressor PID setpoint = %f\n", *compressorPIDsetpoint);
    // stateMachine.compressorPID->Compute();
    // USBSerial.printf("Compressor PID output = %f\n", compressorPIDoutput);

}


void StateMachine::compressorManualSpeed(float speed_percent){

    USBSerial.printf("Setting compressor to manual speed=%f\n", speed_percent);
    compressorPID->SetMode(QuickPID::Control::manual);

    USBSerial.println("...manual compressor speed change complete");

};