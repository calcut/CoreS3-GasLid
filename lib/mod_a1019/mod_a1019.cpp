#include "mod_a1019.h"


void Mod_a1019::readTC_float(float_t tc[8]) {

    USBSerial.print("Reading input values:\n");
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
            USBSerial.printf("TC[%i]: ", i);
            USBSerial.println(tc[i]);
        }
    }
    else {
        USBSerial.print("failed! ");
        USBSerial.println(ModbusRTUClient.lastError());
    }
}
void Mod_a1019::readTC_int(int32_t tc[8]) {

        if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                    96, 8)) {
            USBSerial.print("Input Values integer: ");
            while (ModbusRTUClient.available()) {
                int16_t temperature = ModbusRTUClient.read();
                USBSerial.print(temperature, DEC);
                USBSerial.print(' ');
            }
            USBSerial.println();
        }
}

void Mod_a1019::readTC_int_decimal(int32_t tc[8]) {

        if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                128, 8)) {
            USBSerial.print("Input Values integer_decimal" );
            while (ModbusRTUClient.available()) {
                int16_t temperature = ModbusRTUClient.read();
                USBSerial.print(temperature, DEC);
                USBSerial.print(' ');
            }
            USBSerial.println();
        }
}



void Mod_a1019::setTypeTC(){

    // Set the input types to K type thermocouple
    USBSerial.println("Setting input types to K type thermocouple");

    ModbusRTUClient.beginTransmission(id, HOLDING_REGISTERS, 64, 8);
    for (int i = 0; i < 8; i++) {
        ModbusRTUClient.write(0x0003);
    }
    ModbusRTUClient.endTransmission();
}

void Mod_a1019::getType(){
    // Read the input types
    USBSerial.println("Reading input types");

    if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                64, 8)) {
        USBSerial.print("Input types: 0x ");
        while (ModbusRTUClient.available()) {
            USBSerial.print(ModbusRTUClient.read(), HEX);
            USBSerial.print(' ');
        }
        USBSerial.println();
    }
    else {
        USBSerial.print("failed! ");
        USBSerial.println(ModbusRTUClient.lastError());
    }
}

void Mod_a1019::init(){
    USBSerial.println("\n**** Mod_a1019 init ****");

    if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                MODULE_NAME_ADDR, 1)) {
        USBSerial.print("Module Detected: A-");
        while (ModbusRTUClient.available()) {
            USBSerial.print(ModbusRTUClient.read(), HEX);
            USBSerial.print(' ');
        }
        USBSerial.println();
    }
    else {
        USBSerial.print("A-1019 Module not detected! ");
        USBSerial.println(ModbusRTUClient.lastError());
    }

    setTypeTC();
    getType();
}