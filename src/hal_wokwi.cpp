#include "hal_wokwi.h"

RS485Class RS485(Serial2, PIN_RX_RS485, PIN_TX_RS485, -1, -1);
Outputs outputs;
Inputs inputs;
InputData inputData;
RTC_DS1307 rtc;

OneWire oneWire(10);
DallasTemperature tsensors(&oneWire);

static const uint16_t screenWidth  = LCD_WIDTH; //320
static const uint16_t screenHeight = LCD_HEIGHT; //240

static lv_disp_draw_buf_t disp_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

Adafruit_FT6206 touch = Adafruit_FT6206();
TFT_eSPI tft = TFT_eSPI(screenWidth,screenHeight);

DeviceAddress tc1Addr = { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xA5 };
DeviceAddress tc2Addr = { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x47 };
DeviceAddress tc3Addr = { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x19 };
DeviceAddress tc4Addr = { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x9A };
DeviceAddress tc5Addr = { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xC4 };

char logBuffer[TERMINAL_LOG_LENGTH + 1];

void hal_setup(void){
    Serial.begin(115200);

    // For DEBUG ONLY, otherwise it won't boot without a USB cable
    #ifdef DEBUG
    while (!Serial) {;}
    Serial.println("USB Serial Started");
    #endif

    Wire.begin(2, 1, 400000);  //Init I2C_EXT

    esp_log_level_set("*", ESP_LOG_WARN);
    esp_log_level_set("HAL", ESP_LOG_DEBUG);
    esp_log_set_vprintf(serialLogger);

    ESP_LOGE("HAL", "Error message");
    ESP_LOGW("HAL", "Warning message");
    ESP_LOGI("HAL", "Info message");
    ESP_LOGD("HAL", "Debug message");

    if (! rtc.begin()) {
        ESP_LOGE("HAL", "Couldn't find RTC");
    }
    else{
        ESP_LOGD("HAL", "RTC found");
    }


    setSystemTime();

    inputs.init();
    outputs.init();

    ESP_LOGI("HAL", "hal_setup complete");

};

void Outputs::init() {

    pinMode(19, OUTPUT);
    pinMode(20, OUTPUT);
    pinMode(21, OUTPUT);
    pinMode(47, OUTPUT);
    pinMode(48, OUTPUT);
    pinMode(39, OUTPUT);
    pinMode(40, OUTPUT);
    pinMode(41, OUTPUT);

    
    setFlowValve(0, ValveState::CLOSED);
    setFlowValve(1, ValveState::CLOSED);
    setFlowValve(2, ValveState::CLOSED);
    setFlowValve(3, ValveState::CLOSED);
    setFlowValve(4, ValveState::CLOSED);
    setGasPumpSpeed(0);
    enableJacketHeater(false);
    enableWaterPump(false);
    ESP_LOGI("HAL", "Outputs init complete");

}

void Outputs::setFlowValve(int index, bool ValveState) {
    ESP_LOGI("HAL", "setFlowValve %d %d", index, ValveState);
    switch (index) {
        case 0:
            digitalWrite(19, ValveState);
            break;
        case 1:
            digitalWrite(20, ValveState);
            break;
        case 2:
            digitalWrite(21, ValveState);
            break;
        case 3:
            digitalWrite(47, ValveState);
            break;
        case 4:
            digitalWrite(48, ValveState);
            break;
        default:
            break;
    }
}

void Outputs::setReturnValve(int index, bool ValveState) {
    ESP_LOGI("HAL", "setReturnValve %d %d", index, ValveState);
}

void Outputs::setGasPumpSpeed(float percent) {
    ESP_LOGI("HAL", "setGasPumpSpeed %f", percent);
    analogWrite(41, percent*255);
}

void Outputs::enableJacketHeater(bool enable) {
    ESP_LOGI("HAL", "enableJacketHeater %d", enable);
    digitalWrite(40, enable);
}

bool Outputs::getJacketHeater(void){
    return digitalRead(40);
}

void Outputs::enableWaterPump(bool enable) {
    ESP_LOGI("HAL", "enableWaterPump %d", enable);
    digitalWrite(39, enable);
}

void Inputs::init(void){
    ESP_LOGI("HAL", "Inputs init");
    pinMode(11, INPUT);
    pinMode(12, INPUT);
    pinMode(13, INPUT);
    pinMode(14, INPUT);

    tsensors.begin();
    int deviceCount = tsensors.getDeviceCount();
    ESP_LOGI("HAL", "Found %d temperature sensors", deviceCount);
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
    ESP_LOGW("HAL", "AnalogRead = %0.2f %0.2f %0.2f %0.2f", in1, in2, in3, in4);

    tsensors.requestTemperatures();
    vTaskDelay(100 / portTICK_PERIOD_MS);

    inputData.temperatureData["Tc1"]    = tsensors.getTempC(tc1Addr);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    inputData.temperatureData["Tc2"]    = tsensors.getTempC(tc2Addr);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    inputData.temperatureData["Tc3"]    = tsensors.getTempC(tc3Addr);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    inputData.temperatureData["Tc4"]    = tsensors.getTempC(tc4Addr);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    inputData.temperatureData["Tc5"]    = tsensors.getTempC(tc5Addr);
    vTaskDelay(10 / portTICK_PERIOD_MS);

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

    ESP_LOGW("HAL", "TcX = %0.2f %0.2f %0.2f %0.2f %0.2f",
        inputData.temperatureData["Tc1"],
        inputData.temperatureData["Tc2"],
        inputData.temperatureData["Tc3"],
        inputData.temperatureData["Tc4"],
        inputData.temperatureData["Tc5"]);


}

void Inputs::pollPhysicalControls(void){
    // ESP_LOGD("HAL", "pollPhysicalControls");
}

void setSystemTime(){
    //To set the system time from the simulated Wokwi RTC chip

    DateTime now = rtc.now();

    struct timeval tv;
    tv.tv_sec = now.unixtime();
    tv.tv_usec = 0;

    ESP_LOGI("HAL", "Setting sys time to %02d:%02d:%02d", now.hour(), now.minute(), now.second());

    settimeofday(&tv, NULL);
}

void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp_drv );
}

void my_touchpad_read(lv_indev_drv_t * drv, lv_indev_data_t * data)
{
    bool touched = touch.touched();
    if (touched)
    {
        TS_Point point = touch.getPoint();

        // Print raw touch coordinates
        ESP_LOGD("HAL", "Raw X: %d, Y: %d", point.x, point.y);

        // Map the touch coordinates to match the screen resolution and orientation
        
        uint16_t touchY = map(point.x, 0, 240, 0, 240);
        uint16_t touchX = map(point.y, 0, 320, 320, 0);

        data->point.x = touchX;
        data->point.y = touchY;

        ESP_LOGD("HAL", "Touched at X: %d, Y: %d", touchX, touchY);
    }

    if (!touched)
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;
    }
}

void setRTC(time_t epoch_time, int UTC_offset_minutes){
    //Not implemented because Wokwi sets the time automatically
}

void initDisplay(void){
    lv_init();
    tft.begin();
    tft.setRotation(3);

    if (!touch.begin(40)) {  // pass in 'sensitivity' coefficient
        ESP_LOGE("HAL", "Couldn't start FT6206 touchscreen controller");
    } else {
        ESP_LOGI("HAL", "FT6206 touchscreen controller CONNECTED!");
    }

    lv_disp_draw_buf_init(&disp_buf, buf, NULL, screenWidth*10);

    static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
    disp_drv.flush_cb = my_disp_flush;        /*Set a flush callback to draw to the display*/
    disp_drv.hor_res = screenWidth;                 /*Set the horizontal resolution in pixels*/
    disp_drv.ver_res = screenHeight;                 /*Set the vertical resolution in pixels*/
    lv_disp_t * disp;
    disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

    lv_disp_drv_register(&disp_drv);
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);      /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;                 /*See below.*/
    indev_drv.read_cb = my_touchpad_read;              /*See below.*/
    /*Register the driver in LVGL and save the created input device object*/
    lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv);
    
    //Check vertical and horizontal resolution of what lvgl sees
    lv_coord_t hor_res = lv_disp_get_hor_res(NULL);
    ESP_LOGI("HAL", "LVGL Horizontal Resolution: %d", hor_res);
    
    //Check vertical and horizontal resolution of what lvgl sees
    lv_coord_t ver_res = lv_disp_get_ver_res(NULL);
    ESP_LOGI("HAL", "LVGL Vertical Resolution: %d", ver_res);

    lv_coord_t disp_dpi = lv_disp_get_dpi(NULL);
    ESP_LOGI("HAL", "LVGL Display DPI: %d", disp_dpi);
}

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