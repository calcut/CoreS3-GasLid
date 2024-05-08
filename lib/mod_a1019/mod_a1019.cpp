#include "mod_a1019.h"

void Mod_a1019::getInputs_float(void) {
    ESP_LOGD("a1019", "Reading input values");
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
            memcpy(&AI[i], &byte_array, 4);
            ESP_LOGD("a1019", "AI[%i]: %0.2f", i, AI[i]);
        }
    }
    else {
        ESP_LOGE("a1019", "failed! %s", ModbusRTUClient.lastError());
        for (int i = 0; i < 8; i++) {
            AI[i] = nan("0");
        }
    }
}
void Mod_a1019::readTC_int(int32_t tc[8]) {
    // Not used
    // if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
    //                             96, 8)) {
    //     ESP_LOGD("a1019", "Input Values integer: ");
    //     while (ModbusRTUClient.available()) {
    //         int16_t temperature = ModbusRTUClient.read();
    //         ESP_LOGD("a1019", "%d ", temperature);
    //     }
    // }
}

void Mod_a1019::readTC_int_decimal(int32_t tc[8]) {
    // Not used
    // if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
    //                         128, 8)) {
    //     ESP_LOGD("a1019", "Input Values integer_decimal" );
    //     while (ModbusRTUClient.available()) {
    //         int16_t temperature = ModbusRTUClient.read();
    //         ESP_LOGD("a1019", "%d ", temperature);
    //     }
    // }
}

void Mod_a1019::setType(int channel, channelType type){
    ESP_LOGD("a1019", "Setting input %i to type %i, ", channel, type);

    if (!ModbusRTUClient.holdingRegisterWrite(id, 64 + channel, type)){
        ESP_LOGE("a1019", "failed! %s", ModbusRTUClient.lastError());
    }
}


void Mod_a1019::setTypeTC(){
    // Set the input types to K type thermocouple
    ESP_LOGD("a1019", "Setting input types to K type thermocouple");

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
        
        ESP_LOGD("a1019", "Input types: 0x %s ", logstring);

    }
    else {
        ESP_LOGE("a1019", "failed! %s", ModbusRTUClient.lastError());
    }
}

esp_err_t Mod_a1019::init(int modbus_id){
    ESP_LOGI("a1019", "**** Mod_a1019 init ****");

    id = modbus_id;
    if (ModbusRTUClient.requestFrom(id, HOLDING_REGISTERS,
                            MODULE_NAME_ADDR, 1)) {
        while (ModbusRTUClient.available()) {
            ESP_LOGD("a1019", "Module Detected: A-%X ", ModbusRTUClient.read());
        }
        return ESP_OK;
    }
    else {
        ESP_LOGE("a1019", "A-1019 Module not detected! [%s]", ModbusRTUClient.lastError());
        return ESP_FAIL;
    }
}