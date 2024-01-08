
#include "outputs.h"

Outputs outputs;

void Outputs::init() {

    vTaskDelay(20 / portTICK_PERIOD_MS);
    mod_8AO.init();
    // Set outputs 1-3 to voltage type, default 0 mV
    for (int i = 1; i <= 3; i++) {
        mod_8AO.setOutputType(i, OutputType::VOLTAGE);
        mod_8AO.setOutputVoltageDefault(i, 0);
    }
    vTaskDelay(20 / portTICK_PERIOD_MS);
    mod_16RO.init();
    vTaskDelay(20 / portTICK_PERIOD_MS);

}

// May want to consider timings, and invalid valve combinations.

void Outputs::setEvaporatorValve(ValveState state) {
    //Assumes valves are Normally Closed
    
    // Check evaporator valve and bypass valve are not both closed
    bool bypassState = mod_16RO.getRelay(EVAPORATOR_BYPASS_VALVE_RELAY);
    if (state == ValveState::CLOSED && bypassState == false) {
        USBSerial.println("Error, cannot close Evaporator Valve while Evaporator Bypass Valve is closed");
        return;
    }
    USBSerial.printf("Setting Evaporator Valve to %i\n", state);
    mod_16RO.setRelay(EVAPORATOR_VALVE_RELAY, state);
}

void Outputs::setEvaporatorBypassValve(ValveState state) {
    //Assumes valves are Normally Closed
    bool evapState = mod_16RO.getRelay(EVAPORATOR_VALVE_RELAY);
    if (state == ValveState::CLOSED && evapState == false) {
        USBSerial.println("Error, cannot close Evaporator Bypass Valve while Evaporator Valve is closed");
        return;
    }
    USBSerial.printf("Setting Evaporator Bypass Valve to %i\n", state);
    mod_16RO.setRelay(EVAPORATOR_BYPASS_VALVE_RELAY, state);
}

void Outputs::setReversingValve(ReversingValveState state) {
    //Assumes valve is Normally Forward
    USBSerial.printf("Setting Reversing Valve to %i\n", state);
    mod_16RO.setRelay(REVERSING_VALVE_RELAY, state);
}

void Outputs::setCompressorSpeed(float percent) {
    int mVolts = (int)(percent/100*COMPRESSOR_MAX_VOLTAGE_MV);
    mod_8AO.setOutputVoltage(1, mVolts);
}

void Outputs::setFanSpeed(float percent) {
    int mVolts = (int)(percent/100*FAN_MAX_VOLTAGE_MV);
    mod_8AO.setOutputVoltage(2, mVolts);
}
