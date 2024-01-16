#include "mod_8ao.h"

void Mod_8AO::init(){

    Serial.println("\n**** Mod_8AO init ****");

    if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                MOD_8AO_VERSION, 1)) {
        Serial.print("Module Detected: ");
        while (ModbusRTUClient.available()) {
            Serial.print(ModbusRTUClient.read(), HEX);
            Serial.print(' ');
        }
        Serial.println();
    }
    else {
        Serial.print("Module not detected! ");
        Serial.println(ModbusRTUClient.lastError());
    }

    setWatchdog(10000);
}

void Mod_8AO::setOutputVoltage(int output, int mVolts) {

    // check if output is set to voltage type
    if (output_types[output - 1] != VOLTAGE) {
        Serial.printf("Error, Output %i is not set to voltage type", output);
        return;
    }

    Serial.printf("Setting output %i to %i mVolts... ", output, mVolts);
    int reg = MOD_8AO_OUTPUT1 + (output - 1);
    ModbusRTUClient.beginTransmission(id, HOLDING_REGISTERS,
                                         reg, 1);
    ModbusRTUClient.write(mVolts);
    if (!ModbusRTUClient.endTransmission()) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println("success");
    }
}

void Mod_8AO::setOutputVoltageDefault(int output, int mVolts) {

    // check if output is set to voltage type
    if (output_types[output - 1] != VOLTAGE) {
        Serial.printf("Error, Output %i is not set to voltage type\n", output);
        return;
    }

    Serial.printf("Setting output %i Default to %i mVolts... ", output, mVolts);
    int reg = MOD_8AO_DEFAULT_OUTPUT1 + (output - 1);
    ModbusRTUClient.beginTransmission(id, HOLDING_REGISTERS,
                                         reg, 1);
    ModbusRTUClient.write(mVolts);
    if (!ModbusRTUClient.endTransmission()) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println("success");
    }
}

void Mod_8AO::setOutputCurrent(int output, int uAmps) {

    // check if output is set to current type
    if (output_types[output - 1] != CURRENT_0_20MA) {
        Serial.printf("Output %i is not set to current type", output);
        return;
    }

    Serial.printf("Setting output %i to %i uAmps... ", output, uAmps);
    int reg = MOD_8AO_OUTPUT1 + (output - 1);
    ModbusRTUClient.beginTransmission(id, HOLDING_REGISTERS,
                                         reg, 1);
    ModbusRTUClient.write(uAmps);
    if (!ModbusRTUClient.endTransmission()) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println("success");
    }
}

void Mod_8AO::setOutputCurrentDefault(int output, int uAmps) {

    // check if output is set to current type
    if (output_types[output - 1] != CURRENT_0_20MA) {
        Serial.printf("Output %i is not set to current type", output);
        return;
    }

    Serial.printf("Setting output %i Default to %i uAmps... ", output, uAmps);
    int reg = MOD_8AO_DEFAULT_OUTPUT1 + (output - 1);
    ModbusRTUClient.beginTransmission(id, HOLDING_REGISTERS,
                                         reg, 1);
    ModbusRTUClient.write(uAmps);
    if (!ModbusRTUClient.endTransmission()) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println("success");
    }
}

void Mod_8AO::setOutputType(int output, OutputType type) {
    output_types[output - 1] = type;
    Serial.printf("Setting output %i to type %i... ", output, type);
    int reg = MOD_8AO_OUTPUT_TYPE1 + (output - 1);
    ModbusRTUClient.beginTransmission(id, HOLDING_REGISTERS,
                                         reg, 1);
    ModbusRTUClient.write(type);
    if (!ModbusRTUClient.endTransmission()) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println("success");
    }
}

void Mod_8AO::setWatchdog(int16_t watchdog_ms) {

    if(!ModbusRTUClient.holdingRegisterWrite(id, MOD_8AO_WATCHDOG, watchdog_ms)) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    }
    else Serial.println("success");  
}

int16_t Mod_8AO::getWatchdog(void) {

    Serial.print("Getting mod_8AO Watchdog... ");
    int16_t watchdog_ms;
    watchdog_ms = ModbusRTUClient.holdingRegisterRead(id, MOD_8AO_WATCHDOG);
    if (watchdog_ms == -1) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    }
    else {
        Serial.println(watchdog_ms);
    }
    return watchdog_ms;
}