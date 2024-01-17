#include "mod_a1019.h"

#define TAG "a1019"

void Mod_a1019::readTC_float(float_t tc[8]) {

    ESP_LOGD(TAG, "Reading input values");
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
            ESP_LOGD(TAG, "TC[%i]: %0.2f", i, tc[i]);
        }
    }
    else {
        ESP_LOGE(TAG, "failed! %s", ModbusRTUClient.lastError());
    }
}
void Mod_a1019::readTC_int(int32_t tc[8]) {

        if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                    96, 8)) {
            ESP_LOGD(TAG, "Input Values integer: ");
            while (ModbusRTUClient.available()) {
                int16_t temperature = ModbusRTUClient.read();
                ESP_LOGD(TAG, "%d ", temperature);
            }
        }
}

void Mod_a1019::readTC_int_decimal(int32_t tc[8]) {

        if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                128, 8)) {
            ESP_LOGD(TAG, "Input Values integer_decimal" );
            while (ModbusRTUClient.available()) {
                int16_t temperature = ModbusRTUClient.read();
                ESP_LOGD(TAG, "%d ", temperature);
            }
        }
}

void Mod_a1019::setType(int channel, channelType type){

    ESP_LOGD(TAG, "Setting input %i to type %i, ", channel, type);

    if (!ModbusRTUClient.holdingRegisterWrite(id, 64 + channel, type)){
        ESP_LOGE(TAG, "failed! %s", ModbusRTUClient.lastError());
    }
}


void Mod_a1019::setTypeTC(){

    // Set the input types to K type thermocouple
    ESP_LOGD(TAG, "Setting input types to K type thermocouple");

    ModbusRTUClient.beginTransmission(id, HOLDING_REGISTERS, 64, 8);
    for (int i = 0; i < 8; i++) {
        ModbusRTUClient.write(0x0003);
    }
    ModbusRTUClient.endTransmission();
}

void Mod_a1019::getType(){

    // Read the input types
    char buf[4];
    char logstring[32];

    if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                64, 8)) {
        while (ModbusRTUClient.available()) {
            sprintf(buf, "%X ", ModbusRTUClient.read());
            strcat(logstring, buf);
        }
        
        ESP_LOGD(TAG, "Input types: 0x %s ", logstring);

    }
    else {
        ESP_LOGE(TAG, "failed! %s", ModbusRTUClient.lastError());
    }
}

void Mod_a1019::init(){
    ESP_LOGI(TAG, "**** Mod_a1019 init ****");

    if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                                MODULE_NAME_ADDR, 1)) {
        while (ModbusRTUClient.available()) {
            ESP_LOGD(TAG, "Module Detected: A-%X ", ModbusRTUClient.read());
        }
    }
    else {
        ESP_LOGE(TAG, "A-1019 Module not detected! %s", ModbusRTUClient.lastError());
    }
}