#ifndef HAL_SEPTICSENSOR_H
#define HAL_SEPTICSENSOR_H

#include "config.h"


#include "input_data.h"

#include <Wire.h>
#include <math.h>
#include <ctime>
#include <STM32FreeRTOS.h>

// OUTPUTS
#include <Adafruit_MotorShield.h>

// INPUTS
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
    HAL_ERR_PH_ADC,
    HAL_ERR_MOTORSHIELD,

} hal_err_t;

void errorHandler(hal_err_t err);

//To set the system time from the on-board RTC chip
// void setSystemTime();

//To set the on-board RTC chip from time obtained by notecard
void initRTC();
void setRTC(time_t epoch_time, int UTC_offset_minutes);
int getRTCTime();

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

private:
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
    void pollSensorData(void);
    void pollGasSensors(int tankNumber);

private:

    ADS1115 adc_ph = ADS1115(ADC_PH_ADDR);
    PHProbe phProbe1 = PHProbe(0, &adc_ph);
    PHProbe phProbe2 = PHProbe(1, &adc_ph);
    PHProbe phProbe3 = PHProbe(2, &adc_ph);

};
extern Inputs inputs;


#endif // HAL_SEPTICSENSOR_H
