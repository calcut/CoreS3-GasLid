#ifndef HAL_GASLID_H
#define HAL_GASLID_H

#include <M5Unified.h>
#include "config.h"

#include "input_data.h"

#include <FFat.h>
#include <Wire.h>
#include <ArduinoModbus.h>

//Display
#include <M5GFX.h>
#include <m5gfx_lvgl.h>

// OUTPUTS
#include "MODULE_4IN8OUT.h" //Valve Control
#include "UNIT_HBRIDGE.h" // Motor/Pump Driver

// INPUTS
#include "M5_ADS1100.h" //ADC for gas flow meter
#include "MODULE_4_20MA.h" //Analogue 4-20mA input for gascards
#include "MODULE_DUALKMETER.h" //Thermocouple input module

#ifndef TERMINAL_LOG_LENGTH
#define TERMINAL_LOG_LENGTH 512
#endif

#define ADS_REF_VOLTS 3.72

// Sets up I2C, Serial, Display etc
void hal_setup(void);


typedef enum {
    HAL_ERR_NONE = 1,
    HAL_ERR_I2C,
    HAL_ERR_SPI,
    HAL_ERR_ADC,
    HAL_ERR_GASFLOW_ADC,
    HAL_ERR_PH_ADC,
    HAL_ERR_4IN8OUT,
    HAL_ERR_AIN4_20,
    HAL_ERR_KMETER,
    HAL_ERR_HBRIDGE,

} hal_err_t;

void errorHandler(hal_err_t err);

//To set the system time from the on-board RTC chip
void setSystemTime();

//To set the on-board RTC chip from time obtained by notecard
void setRTC(time_t epoch_time, int UTC_offset_minutes);

void initDisplay(void);

void I2C_scan();

class Outputs {
public:

    enum ValveState {
        OPEN = 1,
        CLOSED = 0
    };

    void init();
    void setFlowValve(int index, bool ValveState);
    void setGasPumpSpeed(float percent);
    void enable12VRelay(bool enable);

private:
    MODULE_4IN8OUT moduleIO;
    UNIT_HBRIDGE gasPumpDriver;

};
extern Outputs outputs;


class Inputs {
public:

    void init(void);
    void serviceFlowMeters(void);
    void pollSensorData(void);
    void pollGasSensors(int tankNumber);
    void pollPhysicalControls(void);

    int err_gasflow_adc_count = 0;
    bool err_gasflow_adc_enabled = false;

    int err_a1019_count = 0;
    bool err_a1019_enabled = false;

    int err_sdm120_count = 0;
    bool err_sdm120_enabled = false;

private:
    MODULE_DUALKMETER thermocoupleReader;
    MODULE_4_20MA gascardReader;
    esp_err_t initFlowMeters(int pin);
    esp_err_t initGasFlowADC();
    float readADCvoltage(void);
    float readThermocouple(int channel);

    ADS1100 ads;

};
extern Inputs inputs;

extern char logBuffer[TERMINAL_LOG_LENGTH + 1];
int serialLogger(const char* format, va_list args);

#endif // HAL_GASLID
