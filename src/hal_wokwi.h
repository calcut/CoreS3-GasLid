#ifndef HAL_WOKWI_H
#define HAL_WOKWI_H

#include <M5Unified.h>
#include "config.h"
#include <ArduinoModbus.h>
#include <Wire.h>
#include "RTClib.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#include "input_data.h"

#include <Adafruit_FT6206.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

// Sets up I2C, Serial, Display etc
void hal_setup(void);
void setSystemTime(void);

//Display related
void initDisplay(void);
void lv_example_btn_1(void);
void my_touchpad_read(lv_indev_drv_t * drv, lv_indev_data_t * data);
void my_disp_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p);

class Outputs {
public:

    enum ValveState {
        OPEN = 1,
        CLOSED = 0
    };

    void init();
    void setFlowValve(int index, bool ValveState);
    void setReturnValve(int index, bool ValveState);
    void setGasPumpSpeed(float percent);
    void enableJacketHeater(bool enable);
    bool getJacketHeater(void);
    void enableWaterPump(bool enable);
};

extern Outputs outputs;

class Inputs {
public:


    void init(void);
    void serviceFlowMeters(void);
    void pollSensorData(void);
    void pollPhysicalControls(void);
};
extern Inputs inputs;

class SerialDisplay : public HWCDC
//https://stackoverflow.com/questions/60972073/customizing-the-standard-serial-print-functions-in-arduino
{
    using HWCDC::HWCDC; // Inherit constructors
    public:
        size_t write(const uint8_t *buffer, size_t size) override;   // Overriding base functionality
        char logBuffer[TERMINAL_LOG_LENGTH + 1];
};
extern SerialDisplay serialDisplay;

#endif // HAL_WOKWI_H
