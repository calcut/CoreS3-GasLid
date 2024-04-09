#include "hal_septicsensor.h"

Outputs outputs;
Inputs inputs;
InputData inputData;

RTC_HandleTypeDef hrtc;
RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef sDate = {0};
RTC_TimeTypeDef currTime = {0};
RTC_DateTypeDef currDate = {0};

bool err;


// RS485Class RS485(Serial2, PIN_RX_RS485, PIN_TX_RS485, PIN_DE_RS485, -1);

void errorHandler(hal_err_t err){

    //Strategy is:
    // Attempt to init the hardware, if it fails, retry up to 3 times
    // If it succeeds, it should be marked as "enabled"

    // Once enabled, if a poll fails, increment the error count and do something sensible
    // e.g. retry the operation or set to a default value like NAN

    
    switch(err){

        case HAL_ERR_PH_ADC:
            printf("ERR - HAL - pH ADC error");
            break;

        case HAL_ERR_MOTORSHIELD:
            printf("ERR - HAL - Motorshield error");
            break;

        default:
            break;
    }
}

void hal_setup(void){
    Serial.begin(9600);
    while(!Serial);
    Serial.println("Serial started");

    Wire.begin(); //Init I2C_SYS (default I2C bus
    // Wire.begin(PIN_SDA_I2C_EXT, PIN_SCL_I2C_EXT, 400000);  //Init I2C_EXT
    // Wire1.begin(PIN_SDA_I2C_SYS, PIN_SCL_I2C_SYS, 400000);  //Init I2C_SYS
    


    ESP_LOGE("HAL", "Error message");
    ESP_LOGW("HAL", "Warning message");
    ESP_LOGI("HAL", "Info message");
    ESP_LOGD("HAL", "Debug message");

    I2C_scan(); // This isn't working for Wire1, super slow and no results. TODO: Fix this

    initRTC();
    setRTC(0, 0);
    getRTCTime();

    inputs.init();
    outputs.init();


    ESP_LOGI("HAL", "hal_setup complete");
    ESP_LOGW("HAL", "Latest Git hash: %s", AUTO_VERSION);

};


void Outputs::init() {
    ESP_LOGI("HAL", "Outputs init");


    if (!MS1.begin()) {         // create with the default frequency 1.6KHz
        // if (!MS1.begin(1000)) {  // OR with a different frequency, say 1KHz
        ESP_LOGW("HAL", "Could not find Motor Shield 1. Check wiring.");
        errorHandler(HAL_ERR_MOTORSHIELD);
    }
    else ESP_LOGI("HAL", "Motor Shield 1 found.");


    setFlowValve(0, ValveState::CLOSED);
    setFlowValve(1, ValveState::CLOSED);
    setFlowValve(2, ValveState::CLOSED);
    setFlowValve(3, ValveState::CLOSED);
    setFlowValve(4, ValveState::CLOSED);
    setFlowValve(5, ValveState::CLOSED);
    
    setReturnValve(0, ValveState::CLOSED);
    setReturnValve(1, ValveState::CLOSED);
    setReturnValve(2, ValveState::CLOSED);
    setReturnValve(3, ValveState::CLOSED);
    setReturnValve(4, ValveState::CLOSED);
    setReturnValve(5, ValveState::CLOSED);
    setGasPumpSpeed(0); 

    // set pin 9 as an output (Jacket Heater), workaround while quadrelay isn't working
    pinMode(PIN_JACKET_RELAY, OUTPUT);
    digitalWrite(PIN_JACKET_RELAY, LOW);

    ESP_LOGI("HAL", "Outputs init complete");
}



void Outputs::setFlowValve(int index, bool ValveState) {

    // bool result = moduleIO1.setOutput(index, ValveState);
    bool result = false;
    ESP_LOGI("HAL", "Flow Valve %d set to %d, success=%d", index, ValveState, result);

}

void Outputs::setReturnValve(int index, bool ValveState) { 
    bool result = false;
    // bool result = moduleIO2.setOutput(index, ValveState);
    ESP_LOGI("HAL", "Return Valve %d set to %d, success=%d", index, ValveState, result);

}

void Outputs::setGasPumpSpeed(float percent) {
    gasPump[0]->setSpeed(percent/100 * 255);
    gasPump[0]->run(FORWARD);
}

void Outputs::enableJacketHeater(bool enable) {
    if(enable){
        // quadRelay.turnRelayOn(JACKET_HEATER_RELAY);
        digitalWrite(PIN_JACKET_RELAY, HIGH);
    }
    else{
        // quadRelay.turnRelayOff(JACKET_HEATER_RELAY);
        digitalWrite(PIN_JACKET_RELAY, LOW);
    }
}

bool Outputs::getJacketHeater(void){
    // return quadRelay.getState(JACKET_HEATER_RELAY);

    // get state of PIN_JACKET_RELAY
    return digitalRead(PIN_JACKET_RELAY);
}


void Inputs::init(void){

    ESP_LOGI("HAL", "Inputs init");
    

    err = adc_ph.begin();
    if (err != true){
        errorHandler(HAL_ERR_PH_ADC);
    }
    else ESP_LOGI("HAL", "pH ADC found");

    ESP_LOGI("HAL", "Inputs init complete");


}


void Inputs::pollSensorData(void){
    ESP_LOGD("HAL", "Polling Sensor Data");

    float AI[8];
    float voltage;


    for (int i = 0; i < 8; i++) {
        AI[i] = NAN;
    }
    

    inputData.temperatureData["ts1"]     = AI[0];
    inputData.temperatureData["ts2"]     = AI[1];
    inputData.temperatureData["ts3"]     = AI[2];
    inputData.temperatureData["tl1"]     = AI[3];
    inputData.temperatureData["tl2"]     = AI[4];
    inputData.temperatureData["tl3"]     = AI[5];
    // inputData.temperatureData["T_flow"]     = AI[2];
    // inputData.temperatureData["T_rtrn"]     = AI[3];
    // inputData.temperatureData["T_biof"]     = AI[4];

    inputData.powerData["JacketOn"]          = (float)outputs.getJacketHeater();


    inputData.pHData["pH1"] = phProbe1.read_ph();
    inputData.pHData["pH2"] = phProbe2.read_ph();
    inputData.pHData["pH3"] = phProbe3.read_ph();

    // adc0 = adc_pH.readVoltage(0);

    // printf("WARNING - HAL - pH Voltages: %d %d %d", adc_pH.readVoltage(0), adc_pH.readVoltage(1), adc_pH.readVoltage(2));
    // inputData.powerData["Power"]            = 0.4;
    // inputData.powerData["Energy"]           = 0.4;


}

void Inputs::pollGasSensors(int tankNumber){
    float AI[8];


    for (int i = 0; i < 8; i++) {
        AI[i] = NAN;
    }

    //Gascard data is 4-20mA, so 20mA = 100% gas, 4mA = 0% gas
    float current = AI[7];
    float gasPercent = (current - 4) / 16 * 100;

    // inputData.gasData["CH4"]                = AI[5];
    // inputData.gasData["CO2"]                = AI[6];
    // inputData.gasData["N2O"]                = AI[7];

    char name[4];
    sprintf(name, "gc%d", tankNumber);

    inputData.gasData[name] = gasPercent;

}

void initRTC(){
    // Initialize RTC
    hrtc.Instance = RTC;
    hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv = 127;
    hrtc.Init.SynchPrediv = 255;
    hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    if (HAL_RTC_Init(&hrtc) != HAL_OK) {
        // Handle error
    }
}


void setRTC(time_t epoch_time, int UTC_offset_minutes){
    //To set the STM32 RTC  from time obtained by notecard
    // struct tm *time_info;

    // epoch_time += UTC_offset_minutes * 60;
    // time_info = localtime(&epoch_time);
    
    // M5.Rtc.setDateTime(time_info);
    // setSystemTime();


    sTime.Hours = 12;
    sTime.Minutes = 34;
    sTime.Seconds = 56;

    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK) {
        // Handle error
    }
    sDate.WeekDay = RTC_WEEKDAY_SATURDAY;
    sDate.Month = RTC_MONTH_MAY;
    sDate.Date = 25;
    sDate.Year = 19;

    if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }
}

int getRTCTime(){


    HAL_RTC_GetTime(&hrtc, &currTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &currDate, RTC_FORMAT_BIN);

    char timeBuff[80];

    sprintf(timeBuff,"%d,,,%d...%d\n", currTime.Hours, currTime.Minutes, currTime.Seconds);
    Serial.println(timeBuff);

    return 123456789;
}

void I2C_scan(){
    byte error, address;
    int nDevices;

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
}

PHProbe::PHProbe(int channel, ADS1115 *adc_ph){
    _adc_ph = adc_ph;
    _channel = channel;
}

float PHProbe::read_ph(){
    _adc_ph->setGain(0);

    int16_t counts = _adc_ph->readADC(_channel);  
    float f = _adc_ph->toVoltage(1);  //  voltage factor
    float voltage = counts * f;

    float slope = (7-4) / (neutralVoltage - acidVoltage); //pH/V

    // Temperature compensation not implemented
    // slope = slope + (slope * temperatureCoefficient*(calibrationTemperature-temperature))

    float ph = (voltage - neutralVoltage) * slope + 7;

    return ph;
}