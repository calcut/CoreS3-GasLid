#include "hal_wokwi.h"

RS485Class RS485(Serial2, PIN_RX_RS485, PIN_TX_RS485, -1, -1);
// RS485Class RS485(Serial2, PIN_RX_RS485, PIN_TX_RS485, PIN_DE_RS485, -1);

void hal_setup(void){
    Serial.begin(115200);

    // For DEBUG ONLY, otherwise it won't boot without a USB cable
    #ifdef DEBUG
    while (!Serial) {;}
    Serial.println("USB Serial Started");
    #endif


    Wire.begin(PIN_SDA_I2C_EXT, PIN_SCL_I2C_EXT, 400000);  //Init I2C_EXT

    Serial.println("Setting log levels");
    esp_log_level_set("*", ESP_LOG_WARN);
    esp_log_level_set("HAL", ESP_LOG_DEBUG);
    // esp_log_set_vprintf(sdCardLogOutput); // Maybe in future

    ESP_LOGE("HAL", "Error message");
    ESP_LOGW("HAL", "Warning message");
    ESP_LOGI("HAL", "Info message");
    ESP_LOGD("HAL", "Debug message");

    ESP_LOGI("HAL", "hal_setup complete");

};


