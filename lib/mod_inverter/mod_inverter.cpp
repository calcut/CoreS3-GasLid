#include "mod_inverter.h"

void Mod_inverter::init(){

    Serial.println("\n**** Mod_inverter init ****");

    Serial.print("Drive Status: ");
    readRegister(INVERTER_DRIVE_STATUS);
    Serial.print("Baud: ");
    readRegister(INVERTER_BAUD);
    Serial.print("Output Frequency: ");
    readRegister(INVERTER_OUTPUT_FREQUENCY);
    Serial.print("Output Power: ");
    readRegister(INVERTER_OUTPUT_POWER);
    Serial.print("Speed Set Point RPS: ");
    readRegister(INVERTER_SPEED_SET_POINT_RPS);
    Serial.print("Command Word: ");
    readRegister(INVERTER_CONTROL_COMMAND_WORD);
    Serial.print("Speed Reference: ");
    readRegister(INVERTER_SPEED_REFERENCE);
    Serial.print("Internal Temperature: ");
    readRegister(INVERTER_INTERNAL_TEMPERATURE);
    Serial.print("KWh Meter: ");
    readRegister(INVERTER_KWH_METER);

    Serial.print("Off Time Countdown: ");
    readRegister(INVERTER_OFF_TIME_COUNTDOWN);

    Serial.print("On Time Countdown: ");
    readRegister(INVERTER_ON_TIME_COUNTDOWN);

    Serial.print("Enabling Drive: ");
    writeRegister(INVERTER_CONTROL_COMMAND_WORD, 0);
    // Serial.print("speed ref idl: ");
    // writeRegister(INVERTER_SPEED_REFERENCE_IDL, 3000);
    Serial.print("speed set point: ");
    writeRegister(INVERTER_SPEED_SET_POINT_RPS, 600);


    // Serial.println("Reading Inverter Network settings");
    // if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
    //                             INVERTER_NETWORK_SETTINGS, 1)) {
    //     Serial.print("Setting Detected: ");
    //     while (ModbusRTUClient.available()) {
    //         Serial.print(ModbusRTUClient.read());
    //         Serial.print(' ');
    //     }
    //     Serial.println();
    // }
    // else {
    //     Serial.print("failed! is module connected? baud rate correct? ");
    //     Serial.println(ModbusRTUClient.lastError());
    //     updateNetworkSettings();
    // }

    // //Set Power Supply Mode to "1" (24Vdc)
    // writeRegister(INVERTER_POWER_SUPPLY_MODE, 1);

    // //Set Refrigerant Type to "7" (R290)
    // writeRegister(INVERTER_REFRIGERANT_TYPE, 7);

    // //Set Main Control to "1" (Multiplexed Cabinet/Cold Room)
    // // writeRegister(INVERTER_MAIN_CONTROL, 1);

    // //Set Main Control to "2" (Self contained cabinet/cold room)
    // writeRegister(INVERTER_MAIN_CONTROL, 2);
    

    // //ENABLE PROBES
    // Serial.println("Enabling S1 probes S1-S4...");
    // writeCoil(INVERTER_S1_ENABLE, true);
    // writeCoil(INVERTER_S2_ENABLE, true);
    // writeCoil(INVERTER_S3_ENABLE, true);
    // writeCoil(INVERTER_S4_ENABLE, true);

    // Serial.println("Setting Probe Types S1-S4...");
    // // Set Probe S1 Type to "6" (0-5V, 0-34.5 barg)
    // writeRegister(INVERTER_S1_CONFIG, 6);
    // // Set Probe S2 Type to "1" (Carel NTC)
    // writeRegister(INVERTER_S2_CONFIG, 1);
    // // Set Probe S3 Type to "6" (0-5V, 0-34.5 barg)
    // writeRegister(INVERTER_S3_CONFIG, 6);
    // // Set Probe S4 Type to "1" (Carel NTC)
    // writeRegister(INVERTER_S4_CONFIG, 1);

    // Serial.println("Reading Inverter PID values");
    // readRegister(INVERTER_KP);
    // readRegister(INVERTER_KI);
    // readRegister(INVERTER_KD);
    // readRegister(INVERTER_SH_SETPOINT);

}

int Mod_inverter::readRegister(int reg){
    int value;
    Serial.printf("Inverter: Reading register %i, ", reg);
    value = ModbusRTUClient.holdingRegisterRead(id, reg);
    if (value == -1) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println(value);
    }
    return value;
}

void Mod_inverter::writeRegister(int reg, int value){
    Serial.printf("Inverter: Writing register %i = %i, ", reg, value);
    if(!ModbusRTUClient.holdingRegisterWrite(id, reg, value)) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    }
    else Serial.println("success");

    
}

// void Mod_inverter::writeRegister(int reg, int value){
//     Serial.printf("Inverter: Writing register %i = %i, ", reg, value);
//     ModbusRTUClient.beginTransmission(id, HOLDING_REGISTERS,
//                                         reg, value);
//     ModbusRTUClient.write(value);
//     if (!ModbusRTUClient.endTransmission()) {
//         Serial.print("failed! ");
//         Serial.println(ModbusRTUClient.lastError());
//     } else {
//         Serial.println("Success");
//     }
// }

void Mod_inverter::writeCoil(int reg, bool value){

    Serial.printf("Inverter: Writing coil %i = %i, ", reg, value);
    if (!ModbusRTUClient.coilWrite(id, reg, value)) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println("Success");
    }
}


// void Mod_inverter::updateNetworkSettings(){

//     Serial.println("Switching to Inverter default Baud rate 19200, SERIAL_8N2");

//     ModbusRTUClient.end();
//     ModbusRTUClient.begin(19200, SERIAL_8N2); // Default for Inverter

//             // Change to Network Setting 5 = 9600 baud, 1 stop, no parity
//     Serial.println("Setting Inverter Network Settings");
//     ModbusRTUClient.beginTransmission(id, HOLDING_REGISTERS,
//                                         INVERTER_NETWORK_SETTINGS, 1);
//     ModbusRTUClient.write(5);
//     if (!ModbusRTUClient.endTransmission()) {
//         Serial.print("failed! ");
//         Serial.println(ModbusRTUClient.lastError());
//     } else {
//         Serial.println("Success, changed to 9600 baud, SERIAL_8N1");
//     }

//     ModbusRTUClient.end();
//     ModbusRTUClient.begin(RS485_BAUD, SERIAL_8N1);
// }

// void Mod_inverter::resetNetworkSettings(){
//     // This is just intended for debug/testing

//     Serial.println("Resetting Inverter Network Settings");
//     ModbusRTUClient.beginTransmission(id, HOLDING_REGISTERS,
//                                         INVERTER_NETWORK_SETTINGS, 1);
//     ModbusRTUClient.write(2); // This is the default
//     if (!ModbusRTUClient.endTransmission()) {
//         Serial.print("failed! ");
//         Serial.println(ModbusRTUClient.lastError());
//     } else {
//         Serial.println("Success, changed to 19200 baud, SERIAL_8N2");
//     }
// }