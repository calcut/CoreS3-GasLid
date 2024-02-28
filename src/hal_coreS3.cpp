#include "hal_coreS3.h"

RS485Class RS485(Serial2, PIN_RX_RS485, PIN_TX_RS485, -1, -1);
Outputs outputs;
Inputs inputs;
InputData inputData;
MODULE_4IN8OUT moduleIO;

char logBuffer[TERMINAL_LOG_LENGTH + 1];
esp_err_t err;


// RS485Class RS485(Serial2, PIN_RX_RS485, PIN_TX_RS485, PIN_DE_RS485, -1);

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

            if (inputs.err_gasflow_adc_count > 5){
                ESP_LOGE("HAL", "Gas Flow ADC not found after 5 attempts. Disabling.");

                //May want to do something else here, like a reset?
                inputs.err_gasflow_adc_enabled = false;
            }
            break;

        case HAL_ERR_A1019:
            inputs.err_a1019_count++;
            ESP_LOGE("HAL", "A1019 not found, error count: %i", inputs.err_a1019_count);

            if (inputs.err_a1019_count > 5){
                ESP_LOGE("HAL", "A1019 not found after 5 attempts. Disabling.");
                inputs.err_a1019_enabled = false;
            }
            break;

        case HAL_ERR_FLOWMETER:
            ESP_LOGE("HAL", "Flowmeter error");
            break;

        case HAL_ERR_4IN8OUT:
            ESP_LOGE("HAL", "4IN8OUT Module error");
            break;

        case HAL_ERR_MOTORSHIELD:
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

// void logSDcard(const char* message){
//     // Write message to log.txt on the SD card
//     // If the file is larger than 1MB, remove lines from the top until it is less than 1MB
//     // If the file does not exist, create it

//     if (SD.exists("/log.txt")){
//         File logFile = SD.open("/log.txt", FILE_APPEND);
//         logFile.println(message);
//         logFile.close();
//     }
//     else{
//         File logFile = SD.open("/log.txt", FILE_WRITE);
//         logFile.println(message);
//         logFile.close();
//     }

//     File logFile = SD.open("/log.txt", FILE_READ);
//     if (logFile.size() > 1000000){
//         //If the file is larger than 1MB, remove lines from the top until it is less than 1MB
//         logFile.seek(0);
//         int lineCount = 0;
//         while (logFile.available()){
//             if (logFile.read() == '\n'){
//                 lineCount++;
//             }
//             if (lineCount > 1000){
//                 break;
//             }
//         }
//         logFile.seek(0);
//         File tempFile = SD.open("/temp.txt", FILE_WRITE);
//         while (logFile.available()){
//             tempFile.write(logFile.read());
//         }
//         logFile.close();
//         tempFile.close();
//         SD.remove("/log.txt");
//         SD.rename("/temp.txt", "/log.txt");
//     }



// }

void Outputs::init() {
    ESP_LOGI("HAL", "Outputs init");

    if (!MS1.begin()) {         // create with the default frequency 1.6KHz
        // if (!MS1.begin(1000)) {  // OR with a different frequency, say 1KHz
        ESP_LOGW("HAL", "Could not find Motor Shield 1. Check wiring.");
        errorHandler(HAL_ERR_MOTORSHIELD);
    }
    else ESP_LOGI("HAL", "Motor Shield 1 found.");

    if (!MS2.begin()) {         // create with the default frequency 1.6KHz
        ESP_LOGW("HAL", "Could not find Motor Shield 2. Check wiring.");
        errorHandler(HAL_ERR_MOTORSHIELD);
    }
    else ESP_LOGI("HAL", "Motor Shield 2 found.");

    if (!MS3.begin()) {         // create with the default frequency 1.6KHz
        ESP_LOGW("HAL", "Could not find Motor Shield 3. Check wiring.");
        errorHandler(HAL_ERR_MOTORSHIELD);
    }
    else ESP_LOGI("HAL", "Motor Shield 3 found.");

    setFlowValve(0, ValveState::CLOSED);
    setFlowValve(1, ValveState::CLOSED);
    setFlowValve(2, ValveState::CLOSED);
    setFlowValve(3, ValveState::CLOSED);
    setFlowValve(4, ValveState::CLOSED);
    setGasPumpSpeed(0); 

    if(!quadRelay.begin())
        ESP_LOGW("HAL", "Could not find Qwiic Relay. Check wiring.");
    else
        ESP_LOGI("HAL", "Qwiic Relay Found.");

    quadRelay.turnAllRelaysOff();


    if(!moduleIO.begin(&Wire1, PIN_SDA_I2C_SYS, PIN_SCL_I2C_SYS, MODULE_4IN8OUT_ADDR)){
        errorHandler(HAL_ERR_4IN8OUT);
    }
    else ESP_LOGI("HAL", "4IN8OUT Module Found");
    

    ESP_LOGI("HAL", "Outputs init complete");
}



void Outputs::setFlowValve(int index, bool ValveState) {
    flowValves[index]->setSpeed(255);
    flowValves[index]->run(ValveState ? FORWARD : RELEASE);
}

void Outputs::setReturnValve(int index, bool ValveState) {
    returnValves[index]->setSpeed(255);
    returnValves[index]->run(ValveState ? FORWARD : RELEASE);
}

void Outputs::setGasPumpSpeed(float percent) {
    gasPump[0]->setSpeed(percent/100 * 255);
    gasPump[0]->run(FORWARD);
}

void Outputs::enableJacketHeater(bool enable) {
    if(enable){
        quadRelay.turnRelayOn(JACKET_HEATER_RELAY);
    }
    else{
        quadRelay.turnRelayOff(JACKET_HEATER_RELAY);
    }
}

bool Outputs::getJacketHeater(void){
    return quadRelay.getState(JACKET_HEATER_RELAY);
}

void Outputs::enableWaterPump(bool enable) {
    quadRelay.turnRelayOn(WATER_PUMP_RELAY);
}


void Inputs::init(void){

    ESP_LOGI("HAL", "Inputs init");
    
    err = mod_a1019.init();
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
        mod_a1019.setType(5, Mod_a1019::TYPE_0_20MA);
        mod_a1019.setType(6, Mod_a1019::TYPE_0_20MA);
        mod_a1019.setType(7, Mod_a1019::TYPE_0_20MA);
        mod_a1019.getType();
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }

    err = initFlowMeters(PIN_PULSE_COUNT);
    if (err != ESP_OK){
        errorHandler(HAL_ERR_FLOWMETER);
    }

    err = initGasFlowADC();
    if (err != ESP_OK){
        errorHandler(HAL_ERR_GASFLOW_ADC);
    }

    ESP_LOGI("HAL", "Inputs init complete");

    // if (gpioExpander.begin() == false) {
    //     Serial.println("Check Connections. No I2C GPIO Expander detected.");
    // }

    // bool pinModes[8] = {GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN};
    // gpioExpander.pinMode(pinModes);
}

esp_err_t Inputs::initGasFlowADC(){
    //ADC for gas flow meter 
    byte error;
    Wire.beginTransmission(ads.ads_i2cAddress);
    error = Wire.endTransmission();
    if (error == 0){  // If the device is connected.
        err_gasflow_adc_enabled = true;
        ads.setGain(GAIN_ONE);  // 1x gain(default)
        ads.setMode(MODE_CONTIN);  // Continuous conversion mode (default)
        ads.setRate(RATE_8);  // 8SPS (default)
        ads.getAddr_ADS1100(
            ADS1100_DEFAULT_ADDRESS);
        ads.setOSMode(
            OSMODE_SINGLE);  // Set to start a single-conversion.
        return ESP_OK;
    }
    else{
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
    ESP_LOGI("HAL", "Flow meter initialised on pin %d", pin);
    return e;
}

void Inputs::serviceFlowMeters(void){

    //Gas flow meter
    inputData.flowData["GasFlow"] = readADCvoltage()*1000/5.0; //5000mV per litre per minute


    pcnt_get_counter_value(PCNT_UNIT_0, &counterVal);

    if (millis() - previousPulseTime != 0){
        flowPPS = ((counterVal - previousPulseCount)*1000)/(millis() - previousPulseTime);
        inputData.flowData["WaterFlow"] = (float)flowPPS * 60 / 4600; //4600 pulses per litre
        ESP_LOGD("HAL", "PPS: %i, Flow: %0.2f", flowPPS, inputData.flowData["WaterFlow"]);

    }

    previousPulseCount = counterVal;
    previousPulseTime = millis();
    
}

void Inputs::pollPhysicalControls(void){

    ESP_LOGD("HAL", "Polling physical controls");

    bool gpioStatus[8];
    uint8_t gpioval;
    gpioval = gpioExpander.digitalReadPort(gpioStatus);

    // if (gpioStatus[1] == 1){
    //     physicalControls.handOffAuto = AUTO;
    // }
    // else if (gpioStatus[0] == 1){
    //     physicalControls.handOffAuto = HAND;
    // }
    // else {
    //     physicalControls.handOffAuto = OFF;
    // }

    // if (gpioStatus[7] == 1){
    //     physicalControls.manualState = DISCHARGING;
    // }
    // else if (gpioStatus[6] == 1){
    //     physicalControls.manualState = DEFROST;
    // }
    // else {
    //     physicalControls.manualState = CHARGING;
    // }

    // ESP_LOGI("HAL", "HandOffAuto: %i, ManualState: %i", physicalControls.handOffAuto, physicalControls.manualState);
    // physicalControls.handOffAuto = HAND;
    // physicalControls.manualState = CHARGING;
}

void Inputs::pollSensorData(void){
    ESP_LOGD("HAL", "Polling Sensor Data");

    float AI[8];
    float voltage;

    if(err_a1019_enabled){
        mod_a1019.getInputs_float(AI);
        // Delay seems to be needed to prevent Modbus errors
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    else{
        for (int i = 0; i < 8; i++) {
            AI[i] = nan("0");
        }
    }

    inputData.temperatureData["T_flow"]     = AI[2];
    inputData.temperatureData["T_rtrn"]     = AI[1];
    inputData.temperatureData["T_shrt"]     = AI[0];
    inputData.temperatureData["T_long"]     = AI[3];
    inputData.temperatureData["T_biof"]     = AI[4];

    inputData.powerData["BatteryVoltage"]    = (float)M5.Power.getBatteryVoltage();
    inputData.powerData["BatteryLevel"]      = (float)M5.Power.getBatteryLevel();
    inputData.powerData["BatteryCurrent"]    = (float)M5.Power.getBatteryCurrent();
    // inputData.powerData["Power"]            = 0.4;
    // inputData.powerData["Energy"]           = 0.4;


}

void Inputs::pollGasSensors(void){
    //Reads the gas sensors and updates the inputData.gasData map
    //The gas sensors are connected to the Mod_a1019 ADC

    float AI[8];

    if(err_a1019_enabled){
        mod_a1019.getInputs_float(AI);
        // Delay seems to be needed to prevent Modbus errors
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    else{
        for (int i = 0; i < 8; i++) {
            AI[i] = nan("0");
        }
    }
    inputData.gasData["CH4"]                = AI[5];
    inputData.gasData["CO2"]                = AI[6];
    inputData.gasData["N2O"]                = AI[7];
}

float Inputs::readADCvoltage(void){

    if (err_gasflow_adc_enabled){
        byte error;
        Wire.beginTransmission(ads.ads_i2cAddress);
        error = Wire.endTransmission();

        if (error == 0)  // If the device is connected.
        {
            int16_t result_raw;
            Wire.requestFrom(ads.ads_i2cAddress, (uint8_t)2);
            result_raw = (int16_t)((Wire.read() << 8) | Wire.read());

            // Reference voltage appears to be ~3.8V on these units. unsure why, should be 3.3V
            // Also, there is a divide by 4 resistor divider on the input.
            float result_volts = result_raw/32768.0 * ADS_REF_VOLTS * 4;
            ESP_LOGD("HAL", "ADC: %0.2f V", result_volts);
            return result_volts;
        } else {
            errorHandler(HAL_ERR_GASFLOW_ADC);
        }
    }
    return nan("0");
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
    tv.tv_sec = mktime(&time_info);
    tv.tv_usec = 0;
    ESP_LOGI("HAL", "Setting sys time to %02d:%02d:%02d", dt.time.hours, dt.time.minutes, dt.time.seconds);
    settimeofday(&tv, NULL);
}

void setRTC(time_t epoch_time, int UTC_offset_minutes){
    //To set the on-board RTC chip from time obtained by notecard
    struct tm *time_info;

    epoch_time += UTC_offset_minutes * 60;
    time_info = localtime(&epoch_time);
    
    M5.Rtc.setDateTime(time_info);
    setSystemTime();
}


void initDisplay(void){
    //Called from setupGUI in gui_helpers.cpp
    lv_init();
    m5gfx_lvgl_init();
}