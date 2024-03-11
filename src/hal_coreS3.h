#ifndef HAL_CORES3_H
#define HAL_CORES3_H

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
#include <Adafruit_MotorShield.h>
#include <SparkFun_Qwiic_Relay.h>
#include "MODULE_4IN8OUT.h"

// INPUTS
#include "mod_a1019.h"  //Temperature sensors
#include "mod_sdm120.h" //Power meter
#include "SparkFun_TCA9534.h" //GPIO Expander for physical Controls
#include <driver/pcnt.h> //ESP32 Pulse counter
#include "M5_ADS1100.h" //ADC for gas flow meter
#include "ADS1X15.h" //ADC for pH probes

#ifndef TERMINAL_LOG_LENGTH
#define TERMINAL_LOG_LENGTH 512
#endif

#define JACKET_HEATER_RELAY 1
#define WATER_PUMP_RELAY 2
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
    HAL_ERR_A1019,
    HAL_ERR_SDM120,
    HAL_ERR_FLOWMETER,
    HAL_ERR_4IN8OUT,
    HAL_ERR_MOTORSHIELD,
    HAL_ERR_QUADRELAY,

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
    void setReturnValve(int index, bool ValveState);
    void setGasPumpSpeed(float percent);
    void enableJacketHeater(bool enable);
    bool getJacketHeater(void);
    void enableWaterPump(bool enable);

private:
    Qwiic_Relay quadRelay = Qwiic_Relay(QUIIC_RELAY_ADDR); // Alternate address 0x6C

    Adafruit_MotorShield MS1 = Adafruit_MotorShield(MOTOR_FEATHERWING_ADDR); //0x6F

    Adafruit_DCMotor *gasPump[1] = {
        MS1.getMotor(4),
    };

};
extern Outputs outputs;

class PHProbe{
    public:
        PHProbe(int channel, ADS1115 *adc_ph);
        float read_ph();
    private:
        ADS1115 *_adc_ph;
        int _channel;
        float neutralVoltage = 1.5;
        float acidVoltage = 2.03244;
        float temperatureCoefficient = 0.00335;
        float calibrationTemperature = 25;

};

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
    esp_err_t initFlowMeters(int pin);
    esp_err_t initGasFlowADC();
    float readADCvoltage(void);

    TCA9534 gpioExpander;
    Mod_a1019 mod_a1019;
    Mod_sdm120 mod_sdm120;
    ADS1100 ads;

    ADS1115 adc_ph = ADS1115(ADC_PH_ADDR);
    PHProbe phProbe1 = PHProbe(0, &adc_ph);
    PHProbe phProbe2 = PHProbe(1, &adc_ph);
    PHProbe phProbe3 = PHProbe(2, &adc_ph);

    int previousPulseCount = 0;
    int previousPulseTime = 0;
    int16_t counterVal;
    int flowPPS;

};
extern Inputs inputs;

extern char logBuffer[TERMINAL_LOG_LENGTH + 1];
int serialLogger(const char* format, va_list args);

#endif // HAL_CORES3_H
