#include "mod_sdm120.h"


float Mod_sdm120::readRegister(int reg) {
    // Serial.printf("Reading register %i, ", reg);
    ESP_LOGD("SDM120", "Reading register %i, ", reg);
    float floatval = -1;

    if (ModbusRTUClient.requestFrom(id, INPUT_REGISTERS,
                                reg, 2)) {
    
        byte byte_array[4];
        uint16_t msbs = ModbusRTUClient.read();
        uint16_t lsbs = ModbusRTUClient.read();

        //Convert msbs and lsbs to IEEE754 32 bit float
        memcpy(&byte_array[2], &msbs, 2);
        memcpy(&byte_array[0], &lsbs, 2);

        // Convert to float and print
        memcpy(&floatval, &byte_array, 4);
        ESP_LOGD("SDM120", "Floatval: %f", floatval);
    }
    else {
        ESP_LOGE("SDM120", "failed! %s while reading register %d", ModbusRTUClient.lastError(), reg);
    }
    return floatval;
}

void Mod_sdm120::writeRegister(int reg, int value) {
    ESP_LOGD("SDM120", "Writing register %i = %i, ", reg, value);
    ModbusRTUClient.beginTransmission(id, HOLDING_REGISTERS,
                                        reg, 1);
    ModbusRTUClient.write(value);
    if (!ModbusRTUClient.endTransmission()) {
        ESP_LOGE("SDM120", "failed! %s while writing register %d", ModbusRTUClient.lastError(), reg);
    } else {
        ESP_LOGD("SDM120", "Success");
    }
}

bool Mod_sdm120::isConnected() {
    int reg = 0;
    bool connected = false;
    if (ModbusRTUClient.requestFrom(id, INPUT_REGISTERS, reg, 2))
    {        
        uint16_t msbs = ModbusRTUClient.read();
        uint16_t lsbs = ModbusRTUClient.read();        
        connected = true;
    }
    else {
        ESP_LOGE("SDM120", "Not Found! %s", ModbusRTUClient.lastError());
        connected = false;
    }
    return connected;
}
