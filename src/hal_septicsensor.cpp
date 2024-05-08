#include "hal_septicsensor.h"

RS485Class RS485(Serial2, PIN_RX_RS485, PIN_TX_RS485, -1, -1);
Outputs outputs;
Inputs inputs;
InputData inputData;
MODULE_4IN8OUT moduleIO1;
MODULE_4IN8OUT moduleIO2;

char logBuffer[TERMINAL_LOG_LENGTH + 1];
esp_err_t err;

SemaphoreHandle_t modbus_mutex = xSemaphoreCreateMutex();
SemaphoreHandle_t I2CMutex = xSemaphoreCreateMutex();

// RS485Class RS485(Serial2, PIN_RX_RS485, PIN_TX_RS485, PIN_DE_RS485, -1);

bool takeI2CMutex(const char* callingFunction) {
    TaskHandle_t currentTask = xTaskGetCurrentTaskHandle();

    if(xSemaphoreTake(I2CMutex, 15000/portTICK_PERIOD_MS) == pdTRUE) {
        ESP_LOGD("HAL", "I2C Mutex taken by %s, %s", pcTaskGetTaskName(currentTask), callingFunction);
        return true;
    }
    else {
        ESP_LOGE("HAL", "I2C Mutex timeout (15s) by %s, %s", pcTaskGetTaskName(currentTask), callingFunction);
        return false;
    }
}

bool takeModbusMutex(const char* callingFunction) {
    TaskHandle_t currentTask = xTaskGetCurrentTaskHandle();


    if(xSemaphoreTake(modbus_mutex, 15000/portTICK_PERIOD_MS) == pdTRUE) {

        //This can prevent modbus errors, under investigation
        //Seems to be needed when changing to talk to a different modbus device
        vTaskDelay(20 / portTICK_PERIOD_MS);

        ESP_LOGD("HAL", "Modbus Mutex taken by %s, %s", pcTaskGetTaskName(currentTask), callingFunction);
        return true;
    }
    else {
        ESP_LOGE("HAL", "Modbus Mutex timeout (15s) by %s, %s", pcTaskGetTaskName(currentTask), callingFunction);
        return false;
    }
}

void errorHandler(hal_err_t err){

    //Strategy is:
    // Attempt to init the hardware, if it fails, retry up to 3 times
    // If it succeeds, it should be marked as "enabled"

    // Once enabled, if a poll fails, increment the error count and do something sensible
    // e.g. retry the operation or set to a default value like nan("0")

    
    switch(err){
        case HAL_ERR_GASFLOW_ADC:
            inputs.err_gasflow_adc_count++;
            ESP_LOGE("HAL", "Gas Flow ADC not found, error count: %i", inputs.err_gasflow_adc_count);

            if (inputs.err_gasflow_adc_count >= 5){
                ESP_LOGE("HAL", "Gas Flow ADC not found after 5 attempts. Disabling.");

                //May want to do something else here, like a reset?
                inputs.err_gasflow_adc_enabled = false;
            }
            break;

        case HAL_ERR_A1019:
            inputs.err_a1019_count++;
            ESP_LOGE("HAL", "A1019 not found, error count: %i", inputs.err_a1019_count);

            if (inputs.err_a1019_count >= 5){
                ESP_LOGE("HAL", "A1019 not found after 5 attempts. Disabling.");
                inputs.err_a1019_enabled = false;
            }
            break;

        case HAL_ERR_A1019_2:
            inputs.err_a1019_2_count++;
            ESP_LOGE("HAL", "A1019_2 not found, error count: %i", inputs.err_a1019_2_count);

            if (inputs.err_a1019_2_count >= 5){
                ESP_LOGE("HAL", "A1019_2 not found after 5 attempts. Disabling.");
                inputs.err_a1019_2_enabled = false;
            }
            break;

        case HAL_ERR_SDM120:
            inputs.err_sdm120_count++;
            ESP_LOGE("HAL", "SDM120 not found, error count: %i", inputs.err_sdm120_count);

            if (inputs.err_sdm120_count >= 5){
                ESP_LOGE("HAL", "SDM120 not found after 5 attempts. Disabling.");
                inputs.err_sdm120_enabled = false;
            }
            break;

        case HAL_ERR_I2C_MUX:
            ESP_LOGE("HAL", "I2C Multiplexer error");
            break;

        case HAL_ERR_FLOWMETER:
            ESP_LOGE("HAL", "Flowmeter error");
            break;

        case HAL_ERR_4IN8OUT:
            ESP_LOGE("HAL", "4IN8OUT Module error");
            break;

        case HAL_ERR_PH_ADC:
            ESP_LOGE("HAL", "pH ADC error, disabling");
            inputs.err_ph_adc_enabled = false;
            break;

        case HAL_ERR_MOISTURE_ADC_1:
            ESP_LOGE("HAL", "Moisture ADC 1 error, disabling");
            inputs.err_moisture_adc_1_enabled = false;
            break;

        case HAL_ERR_MOISTURE_ADC_2:
            ESP_LOGE("HAL", "Moisture ADC 2 error, disabling");
            inputs.err_moisture_adc_2_enabled = false;
            break;

        case HAL_ERR_MOTORSHIELD:
            ESP_LOGE("HAL", "Motorshield error");
            break;

        case HAL_ERR_M5_RELAYS:
            ESP_LOGE("HAL", "M5 Relays error");
            // Probably do something more serious here
            break;

        default:
            break;
    }
}

void hal_setup(void){
    Serial.begin();

    // For DEBUG ONLY, otherwise it won't boot without a USB cable
    #ifdef DEBUG
    // while (!Serial) {;}
    // Serial.println("USB Serial Started");
    #endif

    M5.begin();
    ModbusRTUClient.begin(9600, SERIAL_8N1);

    // The first modbus transaction always fails, so do a dummy read to get it out of the way
    // Don't know why!
    ModbusRTUClient.coilRead(0,0);

    //Default is just boost enabled (so can start from battery), AKA POWER_MODE_USB_IN_BUS_IN
    // M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b10000000, 100000L);  // BOOST_EN = 0
    M5.In_I2C.bitOn(AW9523_ADDR, 0x03, 0b10000000, 100000L);  // BOOST_EN = 1

    // M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00000010, 100000L);  // BUS_OUT_EN = 0
    M5.In_I2C.bitOn(AW9523_ADDR, 0x02, 0b00000010, 100000L);  // BUS_OUT_EN = 1

    M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00100000, 100000L);  // USB_OTG_EN = 0
    // M5.In_I2C.bitOn(AW9523_ADDR, 0x02, 0b00100000, 100000L);  // USB_OTG_EN = 1

    //Power Saving Options
    setCpuFrequencyMhz(240);
    M5.Display.setBrightness(100);

    M5.In_I2C.bitOn(AW9523_ADDR, 0x02, 0b00000001, 100000L);  // TOUCH_RST = 1
    // M5.In_I2C.bitOn(AW9523_ADDR, 0x02, 0b00000100, 100000L);  // AW_RST = 1
    // M5.In_I2C.bitOn(AW9523_ADDR, 0x03, 0b00000001, 100000L);  // CAM_RST = 1
    M5.In_I2C.bitOn(AW9523_ADDR, 0x03, 0b00000010, 100000L);  // LCD_RST = 1

    // M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00000001, 100000L);  // TOUCH_RST = 0 // Touch Off
    M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00000100, 100000L);  // AW_RST = 0 // Audio Amp Off
    M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b00000001, 100000L);  // CAM_RST = 0 //Camera Off
    // M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b00000010, 100000L);  // LCD_RST = 0 //Screen OFF

    //Set Timezone
    setenv("TZ", LOCAL_TIMEZONE, 1);
    tzset();

    // M5.Power.Axp2101.setALDO1(0);    //VDD_1V8 for Audio Amp
    // M5.Power.Axp2101.setALDO2(0);    //VDDA_3V3 for Audio ADC
    // M5.Power.Axp2101.setALDO3(0);    //VDDCAM_3V3
    // M5.Power.Axp2101.setALDO4(0);    //VDD3V3 for SD Card
    // M5.Power.Axp2101.setBLDO1(0);    //AVDD for Camera
    // M5.Power.Axp2101.setBLDO2(0);    //DVDD for Camera
    // M5.Power.Axp2101.setDLDO1(0);    // VCC_BL for LCD backlight
    // M5.Power.Axp2101.setDLDO2(0);    // Not used


    Wire.begin(PIN_SDA_I2C_EXT, PIN_SCL_I2C_EXT, 400000);  //Init I2C_EXT
    Wire1.begin(PIN_SDA_I2C_SYS, PIN_SCL_I2C_SYS, 400000);  //Init I2C_SYS
    

    esp_log_level_set("*", ESP_LOG_WARN);
    esp_log_level_set("HAL", ESP_LOG_DEBUG);
    esp_log_set_vprintf(serialLogger);

    ESP_LOGE("HAL", "Error message");
    ESP_LOGW("HAL", "Warning message");
    ESP_LOGI("HAL", "Info message");
    ESP_LOGD("HAL", "Debug message");

    I2C_scan(); // This isn't working for Wire1, super slow and no results. TODO: Fix this

    ESP_LOGI("HAL", "Battery Level: %d", M5.Power.getBatteryLevel());
    ESP_LOGI("HAL", "Battery Voltage: %d", M5.Power.getBatteryVoltage());
    ESP_LOGI("HAL", "Battery Current: %d", M5.Power.getBatteryCurrent());
    ESP_LOGI("HAL", "BUS Out: %d", M5.Power.getExtOutput());
    ESP_LOGI("HAL", "USB Out: %d", M5.Power.getUsbOutput());
    ESP_LOGI("HAL", "VBUS Voltage: %0.2f", M5.Power.Axp2101.getVBUSVoltage());
    ESP_LOGI("HAL", "VBUS Current: %0.2f", M5.Power.Axp2101.getVBUSCurrent());
    ESP_LOGI("HAL", "ACIN Current: %0.2f", M5.Power.Axp2101.getACINCurrent());
    ESP_LOGI("HAL", "ACIN Voltage: %0.2f", M5.Power.Axp2101.getACINVoltage());

    inputs.init();
    outputs.init();


    ESP_LOGI("HAL", "hal_setup complete");
    ESP_LOGW("HAL", "Latest Git hash: %s", AUTO_VERSION);

};

int serialLogger(const char* format, va_list args){

    // Intended to intercept ESP_LOGx messages and keep them in a log buffer for display on the screen
    char txt_in[TERMINAL_LOG_LENGTH];

    int ret = vsnprintf(txt_in, sizeof(txt_in), format, args);
    Serial.print(txt_in);

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

    return ret;
}

void Outputs::init() {
    ESP_LOGI("HAL", "Outputs init");
    TAKE_I2C_MUTEX_OR_RETURN_VOID();

    if(!moduleIO1.begin(&Wire, PIN_SDA_I2C_SYS, PIN_SCL_I2C_SYS, MODULE_4IN8OUT_1_ADDR)){
        errorHandler(HAL_ERR_4IN8OUT);
    }
    else ESP_LOGI("HAL", "4IN8OUT Module 1 Found");
    
    moduleIO1.setAllOutput(false);

    if(!moduleIO2.begin(&Wire, PIN_SDA_I2C_SYS, PIN_SCL_I2C_SYS, MODULE_4IN8OUT_2_ADDR)){
        errorHandler(HAL_ERR_4IN8OUT);
    }
    else ESP_LOGI("HAL", "4IN8OUT Module 2 Found");
    
    moduleIO2.setAllOutput(false);

    // if (!MS1.begin()) {         // create with the default frequency 1.6KHz
    if (!MS1.begin(400)) {  // OR with a different frequency, say 400Hz
    //400Hz appear to be more stable, less "hunting"
        ESP_LOGW("HAL", "Could not find Motor Shield 1. Check wiring.");
        errorHandler(HAL_ERR_MOTORSHIELD);
    }
    else ESP_LOGI("HAL", "Motor Shield 1 found.");

    initRelays();
    xSemaphoreGive(I2CMutex);

    setFlowValve(0, ValveState::CLOSED);
    setFlowValve(1, ValveState::CLOSED);
    setFlowValve(2, ValveState::CLOSED);
    setFlowValve(3, ValveState::CLOSED);
    setFlowValve(4, ValveState::CLOSED);
    setFlowValve(5, ValveState::CLOSED);
    setFlowValve(6, ValveState::CLOSED);
    setFlowValve(7, ValveState::CLOSED);
    
    setReturnValve(0, ValveState::CLOSED);
    setReturnValve(1, ValveState::CLOSED);
    setReturnValve(2, ValveState::CLOSED);
    setReturnValve(3, ValveState::CLOSED);
    setReturnValve(4, ValveState::CLOSED);
    setReturnValve(5, ValveState::CLOSED);
    setGasPumpSpeed(0); 

    // set pin 9 as an output (Jacket Heater), workaround while quadrelay isn't working
    // pinMode(PIN_JACKET_RELAY, OUTPUT);
    // digitalWrite(PIN_JACKET_RELAY, LOW);

    ESP_LOGI("HAL", "Outputs init complete");
}

void Outputs::initRelays(void){
    int error;
    Wire.beginTransmission(M5_RELAYS_ADDR);
    error = Wire.endTransmission();
    if (error == 0)  // If the device is connected.
    {
        M5Relays.Init(1); // 1=synchronous mode, LEDs match relays
        M5Relays.relayALL(0);
        ESP_LOGI("HAL", "M5 Relays found.");\
    }
    else {
        errorHandler(HAL_ERR_M5_RELAYS);
    }
}

void Outputs::setFlowValve(int index, bool ValveState) {

    TAKE_I2C_MUTEX_OR_RETURN_VOID();
    bool result = moduleIO1.setOutput(index, ValveState);
    ESP_LOGI("HAL", "Flow Valve %d set to %d, success=%d", index, ValveState, result);
    xSemaphoreGive(I2CMutex);

}

void Outputs::setReturnValve(int index, bool ValveState) {

    TAKE_I2C_MUTEX_OR_RETURN_VOID();
    moduleIO2.setAllOutput(false);
    bool result = moduleIO2.setOutput(index, ValveState);
    ESP_LOGI("HAL", "Return Valve %d set to %d, success=%d", index, ValveState, result);
    xSemaphoreGive(I2CMutex);

}

void Outputs::setGasPumpSpeed(float percent) {
    TAKE_I2C_MUTEX_OR_RETURN_VOID();
    gasPump[0]->setSpeed(percent/100 * 255);
    gasPump[0]->run(FORWARD);
    xSemaphoreGive(I2CMutex);
}

void Outputs::enableJacketHeater(bool enable) {
    TAKE_I2C_MUTEX_OR_RETURN_VOID();
    M5Relays.relayWrite(JACKET_HEATER_RELAY, enable);
    xSemaphoreGive(I2CMutex);
}

bool Outputs::getJacketHeater(void){
    TAKE_I2C_MUTEX_OR_RETURN_ZERO();
    Wire.beginTransmission(M5_RELAYS_ADDR);   // Initialize the Tx buffer
    Wire.write(0x11);            // Put slave register address in Tx buffer
    Wire.endTransmission();
    Wire.requestFrom(M5_RELAYS_ADDR, 1);
    uint8_t data = Wire.read();

    bool state = data & (1 << JACKET_HEATER_RELAY);
    xSemaphoreGive(I2CMutex);

    // get state of PIN_JACKET_RELAY
    // return digitalRead(PIN_JACKET_RELAY);
    return state;
}

void Outputs::enableWaterPump(bool enable) {
    TAKE_I2C_MUTEX_OR_RETURN_VOID();
    M5Relays.relayWrite(WATER_PUMP_RELAY, enable);
    xSemaphoreGive(I2CMutex);
}

void Inputs::init(void){

    ESP_LOGI("HAL", "Inputs init");

    TAKE_MODBUS_MUTEX_OR_RETURN_VOID();
    err = mod_a1019.init(MOD_A1019_1_ID);
    if(err != ESP_OK){
        errorHandler(HAL_ERR_A1019);
    }
    else{
        err_a1019_enabled = true;
        mod_a1019.setType(0, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019.setType(1, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019.setType(2, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019.setType(3, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019.setType(4, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019.setType(5, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019.setType(6, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019.setType(7, Mod_a1019::TYPE_0_20MA);
        mod_a1019.getType();
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    xSemaphoreGive(modbus_mutex);

    TAKE_MODBUS_MUTEX_OR_RETURN_VOID();
    err = mod_a1019_2.init(MOD_A1019_2_ID);
    if(err != ESP_OK){
        errorHandler(HAL_ERR_A1019_2);
    }
    else{
        err_a1019_2_enabled = true;
        mod_a1019_2.setType(0, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019_2.setType(1, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019_2.setType(2, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019_2.setType(3, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019_2.setType(4, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019_2.setType(5, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019_2.setType(6, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019_2.setType(7, Mod_a1019::TYPE_THERMOCOUPLE_K);
        mod_a1019_2.getType();
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    xSemaphoreGive(modbus_mutex);

    err_sdm120_enabled = true;

    TAKE_I2C_MUTEX_OR_RETURN_VOID();
    if (I2CMux.begin() == false)
    {
        errorHandler(HAL_ERR_I2C_MUX);
    }
    else ESP_LOGI("HAL", "TCA9548 I2C multiplexer found.");

    err = initFlowMeters(PIN_PULSE_COUNT);
    if (err != ESP_OK){
        errorHandler(HAL_ERR_FLOWMETER);
    }
    else ESP_LOGI("HAL", "Flow meter initialised on pin %d", PIN_PULSE_COUNT);

    I2CMux.selectChannel(ADC_GASFLOW_MUX);
    err = initGasFlowADC();
    if (err != ESP_OK){
        errorHandler(HAL_ERR_GASFLOW_ADC);
    }
    else ESP_LOGI("HAL", "Gas Flow ADC found");

    I2CMux.selectChannel(ADC_PH_MUX);
    if (adc_ph.begin(ADC_PH_ADDR, &Wire))
    {
        ESP_LOGI("HAL", "pH ADC found");
        err_ph_adc_enabled = true;
    }
    else errorHandler(HAL_ERR_PH_ADC);

    I2CMux.selectChannel(ADC_MOISTURE_1_MUX);
    if (adc_moisture_1.begin(ADC_MOISTURE_1_ADDR, &Wire))
    {
        ESP_LOGI("HAL", "Moisture ADC 1 found");
        err_moisture_adc_1_enabled = true;
    }
    else errorHandler(HAL_ERR_MOISTURE_ADC_1);


    I2CMux.selectChannel(ADC_MOISTURE_2_MUX);
    if (adc_moisture_2.begin(ADC_MOISTURE_2_ADDR, &Wire))
    {
        ESP_LOGI("HAL", "Moisture ADC 2 found");
        err_moisture_adc_2_enabled = true;
    }
    else errorHandler(HAL_ERR_MOISTURE_ADC_2);


    I2CMux.disableAllChannels();
    xSemaphoreGive(I2CMutex);
    ESP_LOGI("HAL", "Inputs init complete");

}

esp_err_t Inputs::initGasFlowADC(){
    //ADC for gas flow meter 
    // Intentionally not taking I2CMutex as it is taken in init function
    byte error;
    I2CMux.selectChannel(ADC_GASFLOW_MUX);
    Wire.beginTransmission(ADC_GASFLOW_ADDR);
    error = Wire.endTransmission();
    if (error == 0){  // If the device is connected.
        err_gasflow_adc_enabled = true;
        adc_gasflow.setGain(GAIN_ONE);  // 1x gain(default)
        adc_gasflow.setMode(MODE_CONTIN);  // Continuous conversion mode (default)
        adc_gasflow.setRate(RATE_8);  // 8SPS (default)
        adc_gasflow.getAddr_ADS1100(
            ADS1100_DEFAULT_ADDRESS);
        adc_gasflow.setOSMode(
            OSMODE_SINGLE);  // Set to start a single-conversion.
        I2CMux.disableChannel(ADC_GASFLOW_MUX);
        return ESP_OK;
    }
    else{
        I2CMux.disableChannel(ADC_GASFLOW_MUX);
        return ESP_FAIL;
    }
}

esp_err_t Inputs::initFlowMeters(int pin){
    ESP_LOGI("HAL", "Init Flow Meters");

    pcnt_config_t pcntCh1 = {
        .pulse_gpio_num = pin,
        .ctrl_gpio_num = PCNT_PIN_NOT_USED,
        .lctrl_mode = PCNT_MODE_KEEP,
        .hctrl_mode = PCNT_MODE_KEEP,
        .pos_mode = PCNT_COUNT_DIS,
        .neg_mode = PCNT_COUNT_INC,
        .counter_h_lim = 32767,
        .counter_l_lim = -32768,
        .unit = PCNT_UNIT_0,
        .channel = PCNT_CHANNEL_0,
    };
    esp_err_t e = pcnt_unit_config(&pcntCh1);
    pcnt_counter_clear(PCNT_UNIT_0);
    return e;
}

void Inputs::serviceFlowMeters(void){

    //Gas flow meter
    inputData.flowData["GasFlow"] = readGasFlowADC()*1000/5.0; //5000mV per litre per minute

    pcnt_get_counter_value(PCNT_UNIT_0, &counterVal);

    if (millis() - previousPulseTime != 0){
        flowPPS = ((counterVal - previousPulseCount)*1000)/(millis() - previousPulseTime);
        inputData.flowData["WaterFlow"] = (float)flowPPS * 60 / 4600; //4600 pulses per litre
        ESP_LOGD("HAL", "PPS: %i, Flow: %0.2f", flowPPS, inputData.flowData["WaterFlow"]);

    }

    previousPulseCount = counterVal;
    previousPulseTime = millis();
    
}

void Inputs::pollSensorData(void){
    ESP_LOGD("HAL", "Polling Sensor Data");

    float voltage;

    if(err_a1019_enabled){
        TAKE_MODBUS_MUTEX_OR_RETURN_VOID();
        vTaskDelay(100 / portTICK_PERIOD_MS);
        mod_a1019.getInputs_float();
        xSemaphoreGive(modbus_mutex);
    }
    else{
        for (int i = 0; i < 8; i++) {
            mod_a1019.AI[i] = nan("0");
        }
    }

    inputData.temperatureData["ts1"]     = mod_a1019.AI[0];
    inputData.temperatureData["ts2"]     = mod_a1019.AI[1];
    inputData.temperatureData["ts3"]     = mod_a1019.AI[2];
    inputData.temperatureData["tl1"]     = mod_a1019.AI[3];
    inputData.temperatureData["tl2"]     = mod_a1019.AI[4];
    inputData.temperatureData["tl3"]     = mod_a1019.AI[5];

    if(err_a1019_2_enabled){
        TAKE_MODBUS_MUTEX_OR_RETURN_VOID();
        vTaskDelay(100 / portTICK_PERIOD_MS);
        mod_a1019_2.getInputs_float();
        xSemaphoreGive(modbus_mutex);
    }
    else{
        for (int i = 0; i < 8; i++) {
            mod_a1019_2.AI[i] = nan("0");
        }
    }

    inputData.biofilterTemperatureData["tb1"]     = mod_a1019_2.AI[0];
    inputData.biofilterTemperatureData["tb2"]     = mod_a1019_2.AI[1];
    inputData.biofilterTemperatureData["tb3"]     = mod_a1019_2.AI[2];
    inputData.biofilterTemperatureData["tb4"]     = mod_a1019_2.AI[3];
    inputData.biofilterTemperatureData["tb5"]     = mod_a1019_2.AI[4];
    inputData.biofilterTemperatureData["tb6"]     = mod_a1019_2.AI[5];
    inputData.biofilterTemperatureData["tb7"]     = mod_a1019_2.AI[6];
    inputData.biofilterTemperatureData["tb8"]     = mod_a1019_2.AI[7];


    if(err_sdm120_enabled){
        TAKE_MODBUS_MUTEX_OR_RETURN_VOID();
        if(mod_sdm120.isConnected()){
            inputData.powerData["Voltage"]           = mod_sdm120.readRegister(SDM120_VOLTAGE);
            inputData.powerData["Power"]             = mod_sdm120.readRegister(SDM120_ACTIVE_POWER);
            inputData.powerData["PowerApparent"]     = mod_sdm120.readRegister(SDM120_APPARENT_POWER);
            inputData.powerData["Energy"]            = mod_sdm120.readRegister(SDM120_TOTAL_ACTIVE_ENERGY);
        }
        else{
            errorHandler(HAL_ERR_SDM120);
        }
        xSemaphoreGive(modbus_mutex);
    }

    if(err_ph_adc_enabled){
        inputData.pHData["pH1"] = phProbe1.read_ph();
        inputData.pHData["pH2"] = phProbe2.read_ph();
        inputData.pHData["pH3"] = phProbe3.read_ph();
    }

    if(err_moisture_adc_1_enabled){
        inputData.moistureData["ms1"] = moistureProbe1.readMoisture_pc();
        inputData.moistureData["ms2"] = moistureProbe2.readMoisture_pc();
        inputData.moistureData["ms3"] = moistureProbe3.readMoisture_pc();
    }
    if(err_moisture_adc_2_enabled){
        inputData.moistureData["ms4"] = moistureProbe4.readMoisture_pc();
        inputData.moistureData["ms5"] = moistureProbe5.readMoisture_pc();
        inputData.moistureData["ms6"] = moistureProbe6.readMoisture_pc();
    }

    inputData.powerData["BatteryVoltage"]    = (float)M5.Power.getBatteryVoltage();
    inputData.powerData["BatteryLevel"]      = (float)M5.Power.getBatteryLevel();
    inputData.powerData["BatteryCurrent"]    = (float)M5.Power.getBatteryCurrent();
    inputData.powerData["JacketOn"]          = (float)outputs.getJacketHeater();


}

void Inputs::pollGasSensors(int tankNumber){

    if(err_a1019_enabled){
        TAKE_MODBUS_MUTEX_OR_RETURN_VOID();
        mod_a1019.getInputs_float();
        xSemaphoreGive(modbus_mutex);
    }
    else{
        for (int i = 0; i < 8; i++) {
            mod_a1019.AI[i] = nan("0");
        }
    }

    //Gascard data is 4-20mA, so 20mA = 100% gas, 4mA = 0% gas
    float current = mod_a1019.AI[7];
    float gasPercent = (current - 4) / 16 * 100;

    // inputData.gasData["CH4"]                = AI[5];
    // inputData.gasData["CO2"]                = AI[6];
    // inputData.gasData["N2O"]                = AI[7];

    char name[4];
    sprintf(name, "gc%d", tankNumber);

    inputData.gasData[name] = gasPercent;

}

float Inputs::readGasFlowADC(void){

    float result_volts = nan("0");

    if (err_gasflow_adc_enabled){
        TAKE_I2C_MUTEX_OR_RETURN_ZERO();
        I2CMux.selectChannel(ADC_GASFLOW_MUX);  
        byte error;
        Wire.beginTransmission(adc_gasflow.ads_i2cAddress);
        error = Wire.endTransmission();

        if (error == 0)  // If the device is connected.
        {
            int16_t result_raw;
            Wire.requestFrom(adc_gasflow.ads_i2cAddress, (uint8_t)2);
            result_raw = (int16_t)((Wire.read() << 8) | Wire.read());

            // Reference voltage appears to be ~3.8V on these units. unsure why, should be 3.3V
            // Also, there is a divide by 4 resistor divider on the input.
            result_volts = result_raw/32768.0 * ADS_REF_VOLTS * 4;
        } else {
            errorHandler(HAL_ERR_GASFLOW_ADC);
        }
        I2CMux.disableChannel(ADC_GASFLOW_MUX);
        xSemaphoreGive(I2CMutex);
    }
    return result_volts;
}

void setSystemTime(){
    //To set the system time from the on-board RTC chip

    struct tm time_info;
    m5::rtc_datetime_t dt = M5.Rtc.getDateTime();

    time_info.tm_hour = dt.time.hours;
    time_info.tm_min = dt.time.minutes;
    time_info.tm_sec = dt.time.seconds;
    time_info.tm_wday = dt.date.weekDay;
    time_info.tm_mon = dt.date.month - 1;
    time_info.tm_mday = dt.date.date;
    time_info.tm_year = dt.date.year - 1900;

    struct timeval tv;

    //Need to briefly switch to GMT0 so mktime knows that time_info is in GMT
    setenv("TZ", "GMT0", 1);
    tzset();

    tv.tv_sec = mktime(&time_info);
    tv.tv_usec = 0;

    //then switch back to local timezone
    setenv("TZ", LOCAL_TIMEZONE, 1);
    tzset();

    settimeofday(&tv, NULL);

    gettimeofday(&tv, NULL);
    char localtime_str[12];
    char utctime_str[12];
    strftime(localtime_str, sizeof(localtime_str), "%X", localtime(&tv.tv_sec));
    strftime(utctime_str, sizeof(utctime_str), "%X", gmtime(&tv.tv_sec));

    ESP_LOGI("HAL", "Sys time set to %s UTC, %s local", utctime_str, localtime_str);

}

void setRTC(time_t epoch_time, int UTC_offset_minutes){
    //To set the on-board RTC chip from time obtained by notecard
    struct tm *time_info;

    time_info = gmtime(&epoch_time);
    
    //RTC is set in GMT / UTC only, as it is not timezone aware
    M5.Rtc.setDateTime(time_info);
    setSystemTime();
}


void initDisplay(void){
    //Called from setupGUI in gui_helpers.cpp
    lv_init();
    m5gfx_lvgl_init();
}

void I2C_scan(){
    byte error, address;
    int nDevices;

    TAKE_I2C_MUTEX_OR_RETURN_VOID();
    Serial.println("Scanning...");

    nDevices = 0;
    for(address = 1; address < 127; address++ )
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
        Serial.print("I2C EXT (Wire) device found at address 0x");
        if (address<16)
            Serial.print("0");
        Serial.print(address,HEX);
        Serial.println("  !");

        nDevices++;
        }
        else if (error==4)
        {
        Serial.print("Unknown error at address 0x");
        if (address<16)
            Serial.print("0");
        Serial.println(address,HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");
    xSemaphoreGive(I2CMutex);
}

PHProbe::PHProbe(int channel, Adafruit_ADS1115 *adc, int muxChannel, PCA9548 *mux){
    _adc = adc;
    _channel = channel;
    _muxChannel = muxChannel;
    _mux = mux;
}

float PHProbe::read_ph(){
    ESP_LOGD("HAL", "Reading pH Probe %d", _channel);

    TAKE_I2C_MUTEX_OR_RETURN_ZERO();
    _mux->selectChannel(_muxChannel);

    int counts = _adc->readADC_SingleEnded(_channel);
    float voltage = _adc->computeVolts(counts);

    float slope = (7-4) / (neutralVoltage - acidVoltage); //pH/V

    // Temperature compensation not implemented
    // slope = slope + (slope * temperatureCoefficient*(calibrationTemperature-temperature))

    float ph = (voltage - neutralVoltage) * slope + 7;

    _mux->disableChannel(_muxChannel);
    xSemaphoreGive(I2CMutex);

    return ph;
}

MoistureProbe::MoistureProbe(int channel, Adafruit_ADS1115 *adc, int muxChannel, PCA9548 *mux){
    _adc = adc;
    _channel = channel;
    _muxChannel = muxChannel;
    _mux = mux;
}
float MoistureProbe::readMoisture_pc(){
    ESP_LOGD("HAL", "Reading Moisture Probe %d", _channel);

    TAKE_I2C_MUTEX_OR_RETURN_ZERO();
    _mux->selectChannel(_muxChannel);

    int counts = _adc->readADC_SingleEnded(_channel);
    float voltage = _adc->computeVolts(counts);
    float moisture_pc = 100 - ((voltage - waterVoltage) / (airVoltage - waterVoltage) * 100);

    _mux->disableChannel(_muxChannel);
    xSemaphoreGive(I2CMutex);

    return moisture_pc;
}