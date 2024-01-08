#include "mod_sdm120.h"


void Mod_sdm120::init() {
    // Initialization code here
    // You might need to write to or read from some registers
}

// void Mod_sdm120::readVoltage(float *voltage) {
//     USBSerial.print("Reading voltage, ");
//     // ModbusRTUClient.end();
//     // ModbusRTUClient.begin(2400);
//     // readRegister(SDM120_VOLTAGE);
//     readRegister(0);
//     // readRegister(2);
//     // readRegister(3);
//     // readRegister(4);
//     // readRegister(5);
//     readRegister(70);
//     // readRegister(71);


//     // readRegister(SDM120_VOLTAGE_LO);
//     // ModbusRTUClient.end();
//     // ModbusRTUClient.begin(9600);
//     // readRegister(SDM120_VOLTAGE_HI);
//     // readRegister(SDM120_VOLTAGE_LO);
// }



float Mod_sdm120::readRegister(int reg) {
    USBSerial.printf("Reading register %i, ", reg);
    float floatval = -1;

    if (ModbusRTUClient.requestFrom(id, INPUT_REGISTERS,
                                reg, 2)) {
        USBSerial.print("Success: ");
    
        byte byte_array[4];
        uint16_t msbs = ModbusRTUClient.read();
        uint16_t lsbs = ModbusRTUClient.read();

        //Convert msbs and lsbs to IEEE754 32 bit float
        memcpy(&byte_array[2], &msbs, 2);
        memcpy(&byte_array[0], &lsbs, 2);

        // Convert to float and print
        memcpy(&floatval, &byte_array, 4);
        USBSerial.printf("Floatval: %f\n", floatval);
    }
    else {
        USBSerial.print("failed! ");
        USBSerial.println(ModbusRTUClient.lastError());
    }
    return floatval;
}

void Mod_sdm120::writeRegister(int reg, int value) {
    USBSerial.printf("Writing register %i = %i, ", reg, value);
    ModbusRTUClient.beginTransmission(id, HOLDING_REGISTERS,
                                        reg, 1);
    ModbusRTUClient.write(value);
    if (!ModbusRTUClient.endTransmission()) {
        USBSerial.print("failed! ");
        USBSerial.println(ModbusRTUClient.lastError());
    } else {
        USBSerial.println("Success");
    }
}