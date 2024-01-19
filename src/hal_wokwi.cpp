#include "hal_wokwi.h"

RS485Class RS485(Serial2, PIN_RX_RS485, PIN_TX_RS485, -1, -1);
Outputs outputs;
Inputs inputs;
InputData inputData;

void hal_setup(void){
    Serial.begin(115200);

    // For DEBUG ONLY, otherwise it won't boot without a USB cable
    #ifdef DEBUG
    while (!Serial) {;}
    Serial.println("USB Serial Started");
    #endif

    Serial.println("Setting log levels");
    esp_log_level_set("*", ESP_LOG_WARN);
    esp_log_level_set("HAL", ESP_LOG_DEBUG);
    // esp_log_set_vprintf(sdCardLogOutput); // Maybe in future

    ESP_LOGE("HAL", "Error message");
    ESP_LOGW("HAL", "Warning message");
    ESP_LOGI("HAL", "Info message");
    ESP_LOGD("HAL", "Debug message");

    inputs.init();
    outputs.init();

    ESP_LOGI("HAL", "hal_setup complete");

};

void Outputs::init() {
    
    setFlowValve(0, ValveState::CLOSED);
    setFlowValve(1, ValveState::CLOSED);
    setFlowValve(2, ValveState::CLOSED);
    setFlowValve(3, ValveState::CLOSED);
    setFlowValve(4, ValveState::CLOSED);
    setGasPumpSpeed(0);
    ESP_LOGI("HAL", "Outputs init complete");

}

void Outputs::setFlowValve(int index, bool ValveState) {
    ESP_LOGI("HAL", "setFlowValve %d %d", index, ValveState);
}

void Outputs::setReturnValve(int index, bool ValveState) {
    ESP_LOGI("HAL", "setReturnValve %d %d", index, ValveState);
}

void Outputs::setGasPumpSpeed(float percent) {
    ESP_LOGI("HAL", "setGasPumpSpeed %f", percent);
}

void Outputs::enableJacketHeater(bool enable) {
    ESP_LOGI("HAL", "enableJacketHeater %d", enable);
}

void Outputs::enableWaterPump(bool enable) {
    ESP_LOGI("HAL", "enableWaterPump %d", enable);
}

void Inputs::init(void){
    ESP_LOGI("HAL", "Inputs init");
    pinMode(11, INPUT);
    pinMode(12, INPUT);
    pinMode(13, INPUT);
    pinMode(14, INPUT);

}

void Inputs::serviceFlowMeters(void){
    // ESP_LOGD("HAL", "serviceFlowMeters");
}

void Inputs::pollSensorData(void){
    ESP_LOGD("HAL", "Polling Sensor Data (Simulated)");

    int mintemp = 0;
    int maxtemp = 50;

    float in1 = analogRead(11)/4095.0*(maxtemp-mintemp)+mintemp;
    float in2 = analogRead(12)/4095.0*(maxtemp-mintemp)+mintemp;
    float in3 = analogRead(13)/4095.0*(maxtemp-mintemp)+mintemp;
    float in4 = analogRead(14)/4095.0*(maxtemp-mintemp)+mintemp;
    ESP_LOGW("HAL", "AnalogRead = %f %f %f %f", in1, in2, in3, in4);

    inputData.temperatureData["Tc1"]    = 0.1;
    inputData.temperatureData["Tc2"]    = 0.1;
    inputData.temperatureData["Tc3"]    = 0.1;
    inputData.temperatureData["Tc4"]    = 0.1;
    inputData.temperatureData["Tc5"]    = 0.1;
    inputData.pressureData["Pr1"]       = 0.2;
    inputData.pressureData["Pr2"]       = 0.2;
    inputData.pressureData["Pr3"]       = 0.2;
    inputData.pressureData["Pr4"]       = 0.2;
    inputData.flowData["WaterFlow"]     = 0.3;
    inputData.flowData["GasFlow"]       = 0.3;
    inputData.powerData["Power"]        = 0.4;
    inputData.powerData["Energy"]       = 0.4;
    inputData.gasData["CH4"]            = 0.5;
    inputData.gasData["CO2"]            = 0.5;
    inputData.gasData["N2O"]            = 0.5;
}

void Inputs::pollPhysicalControls(void){
    // ESP_LOGD("HAL", "pollPhysicalControls");
}

size_t SerialDisplay::write(const uint8_t *buffer, size_t size){

    // This intercepts SerialDisplay.print() and similar.
    // It captures the text and appends it to the end of a log buffer for display on the screen

    char *txt_in = (char*)buffer;
    uint16_t txt_len = strlen(txt_in);
    uint16_t old_len = strlen(logBuffer); 

    //Append the new text to the end of the log, deleting the oldest text if necessary
    if (old_len + txt_len > TERMINAL_LOG_LENGTH){
        //If the new text is longer than the log, then delete the oldest text
        uint16_t new_start = old_len - (TERMINAL_LOG_LENGTH - txt_len);
        uint16_t new_len = old_len - new_start;
        memcpy(logBuffer, &logBuffer[new_start], new_len);
        memcpy(&logBuffer[new_len], txt_in, txt_len);

        logBuffer[new_len+txt_len] = '\0';
    }
    else{
        //If the new text is shorter than the log, then append it to the end
        memcpy(&logBuffer[old_len], txt_in, txt_len);
        logBuffer[old_len + txt_len] = '\0';
    }

    return HWCDC::write(buffer, size);
}
SerialDisplay serialDisplay;