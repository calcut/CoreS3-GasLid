#include "mod_a1019.h"


void Mod_a1019::readTC_float(float_t tc[8]) {

    Serial.print("Reading input values:\n");
    if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                736, 16)) {  //ABCD

        for (int i = 0; i < 8; i++) {
            byte byte_array[4];
            uint16_t msbs = ModbusRTUClient.read();
            uint16_t lsbs = ModbusRTUClient.read();

            // Put bytes in the correct order
            memcpy(&byte_array[2], &msbs, 2);
            memcpy(&byte_array[0], &lsbs, 2);

            // Convert to float and print
            memcpy(&tc[i], &byte_array, 4);
            Serial.printf("TC[%i]: ", i);
            Serial.println(tc[i]);
        }
    }
    else {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    }
}
void Mod_a1019::readTC_int(int32_t tc[8]) {

        if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                    96, 8)) {
            Serial.print("Input Values integer: ");
            while (ModbusRTUClient.available()) {
                int16_t temperature = ModbusRTUClient.read();
                Serial.print(temperature, DEC);
                Serial.print(' ');
            }
            Serial.println();
        }
}

void Mod_a1019::readTC_int_decimal(int32_t tc[8]) {

        if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                128, 8)) {
            Serial.print("Input Values integer_decimal" );
            while (ModbusRTUClient.available()) {
                int16_t temperature = ModbusRTUClient.read();
                Serial.print(temperature, DEC);
                Serial.print(' ');
            }
            Serial.println();
        }
}

void Mod_a1019::setType(int channel, channelType type){

    Serial.printf("Setting input %i to type %i, ", channel, type);

    if (!ModbusRTUClient.holdingRegisterWrite(id, 64 + channel, type)){
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println("Success!");
    }
}


void Mod_a1019::setTypeTC(){

    // Set the input types to K type thermocouple
    Serial.println("Setting input types to K type thermocouple");

    ModbusRTUClient.beginTransmission(id, HOLDING_REGISTERS, 64, 8);
    for (int i = 0; i < 8; i++) {
        ModbusRTUClient.write(0x0003);
    }
    ModbusRTUClient.endTransmission();
}

void Mod_a1019::getType(){
    // Read the input types
    Serial.println("Reading input types");

    if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                64, 8)) {
        Serial.print("Input types: 0x ");
        while (ModbusRTUClient.available()) {
            Serial.print(ModbusRTUClient.read(), HEX);
            Serial.print(' ');
        }
        Serial.println();
    }
    else {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    }
}

void Mod_a1019::init(){
    Serial.println("\n**** Mod_a1019 init ****");

    if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                MODULE_NAME_ADDR, 1)) {
        Serial.print("Module Detected: A-");
        while (ModbusRTUClient.available()) {
            Serial.print(ModbusRTUClient.read(), HEX);
            Serial.print(' ');
        }
        Serial.println();
    }
    else {
        Serial.print("A-1019 Module not detected! ");
        Serial.println(ModbusRTUClient.lastError());
    }
}