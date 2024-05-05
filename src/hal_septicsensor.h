#ifndef HAL_SEPTICSENSOR_H
#define HAL_SEPTICSENSOR_H

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
#include "Unit_4RELAY.h"

// INPUTS
#include "mod_a1019.h"  //Temperature sensors
#include "mod_sdm120.h" //Power meter
#include <driver/pcnt.h> //ESP32 Pulse counter
#include "M5_ADS1100.h" //ADC for gas flow meter
#include <Adafruit_ADS1X15.h>  //ADC for pH probes and moisture sensors
#include "TCA9548.h" //I2C Multiplexer

#ifndef TERMINAL_LOG_LENGTH
#define TERMINAL_LOG_LENGTH 512
#endif

#define JACKET_HEATER_RELAY 0
#define WATER_PUMP_RELAY 2
#define ADS_REF_VOLTS 3.72

//To prevent concurrent access to I2C bus
//Delcared extern so RTOS tasks can access it for managing notecard access
extern SemaphoreHandle_t I2CMutex;
extern bool takeI2CMutex(const char* callingFunction);
extern bool takeModbusMutex(const char* callingFunction);

//Macro to simplify I2C mutex handling
//Function will return if mutex is not available
#define TAKE_I2C_MUTEX_OR_RETURN_ZERO() \
do { \
    if(!takeI2CMutex(__func__)) { \
        return 0; \
    } \
} while(0)

#define TAKE_I2C_MUTEX_OR_RETURN_VOID() \
do { \
    if(!takeI2CMutex(__func__)) { \
        return; \
    } \
} while(0)

#define TAKE_MODBUS_MUTEX_OR_RETURN_ZERO() \
do { \
    if(!takeModbusMutex(__func__)) { \
        return 0; \
    } \
} while(0)

#define TAKE_MODBUS_MUTEX_OR_RETURN_VOID() \
do { \
    if(!takeModbusMutex(__func__)) { \
        return; \
    } \
} while(0)

// Sets up I2C, Serial, Display etc
void hal_setup(void);


typedef enum {
    HAL_ERR_NONE = 1,
    HAL_ERR_I2C,
    HAL_ERR_SPI,
    HAL_ERR_ADC,
    HAL_ERR_GASFLOW_ADC,
    HAL_ERR_PH_ADC,
    HAL_ERR_MOISTURE_ADC_1,
    HAL_ERR_MOISTURE_ADC_2,
    HAL_ERR_I2C_MUX,
    HAL_ERR_A1019,
    HAL_ERR_A1019_2,
    HAL_ERR_SDM120,
    HAL_ERR_FLOWMETER,
    HAL_ERR_4IN8OUT,
    HAL_ERR_MOTORSHIELD,
    HAL_ERR_M5_RELAYS,

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
    void initRelays(void);
    void setFlowValve(int index, bool ValveState);
    void setReturnValve(int index, bool ValveState);
    void setGasPumpSpeed(float percent);
    void enableJacketHeater(bool enable);
    bool getJacketHeater(void);
    void enableWaterPump(bool enable);

private:

    UNIT_4RELAY M5Relays;
    Adafruit_MotorShield MS1 = Adafruit_MotorShield(MOTOR_FEATHERWING_ADDR); //0x6F
    Adafruit_DCMotor *gasPump[1] = {
        MS1.getMotor(4),
    };

};
extern Outputs outputs;

class PHProbe{
    public:
        PHProbe(int channel, Adafruit_ADS1115 *adc, int muxChannel, PCA9548 *mux);
        float read_ph();
    private:
        Adafruit_ADS1115 *_adc;
        int _channel;
        PCA9548 *_mux;
        int _muxChannel;
        float neutralVoltage = 1.5;
        float acidVoltage = 2.03244;
        float temperatureCoefficient = 0.00335;
        float calibrationTemperature = 25;

};

class MoistureProbe{
    public:
        MoistureProbe(int channel, Adafruit_ADS1115 *adc, int muxChannel, PCA9548 *mux);
        float readMoisture_pc();
    private:
        Adafruit_ADS1115 *_adc;
        int _channel;
        PCA9548 *_mux;
        int _muxChannel;
        float airVoltage = 2.25;
        float waterVoltage = 0;
};

class Inputs {
public:

    void init(void);
    void serviceFlowMeters(void);
    void pollSensorData(void);
    void pollGasSensors(int tankNumber);

    int err_gasflow_adc_count = 0;
    bool err_gasflow_adc_enabled = false;

    int err_a1019_count = 0;
    bool err_a1019_enabled = false;

    int err_a1019_2_count = 0;
    bool err_a1019_2_enabled = false;

    int err_sdm120_count = 0;
    bool err_sdm120_enabled = false;

    bool err_ph_adc_enabled = false;
    bool err_moisture_adc_1_enabled = false;
    bool err_moisture_adc_2_enabled = false;

private:
    esp_err_t initFlowMeters(int pin);
    esp_err_t initGasFlowADC();
    float readGasFlowADC(void);

    Mod_a1019 mod_a1019;
    Mod_a1019 mod_a1019_2;
    Mod_sdm120 mod_sdm120;

    PCA9548 I2CMux = PCA9548(I2C_MUX_ADDR, &Wire);
    ADS1100 adc_gasflow;

    Adafruit_ADS1115 adc_ph;
    Adafruit_ADS1115 adc_moisture_1;
    Adafruit_ADS1115 adc_moisture_2;

    PHProbe phProbe1 = PHProbe(0, &adc_ph, ADC_PH_MUX, &I2CMux);
    PHProbe phProbe2 = PHProbe(1, &adc_ph, ADC_PH_MUX, &I2CMux);
    PHProbe phProbe3 = PHProbe(2, &adc_ph, ADC_PH_MUX, &I2CMux);

    MoistureProbe moistureProbe1 = MoistureProbe(0, &adc_moisture_1, ADC_MOISTURE_1_MUX, &I2CMux);
    MoistureProbe moistureProbe2 = MoistureProbe(1, &adc_moisture_1, ADC_MOISTURE_1_MUX, &I2CMux);
    MoistureProbe moistureProbe3 = MoistureProbe(2, &adc_moisture_1, ADC_MOISTURE_1_MUX, &I2CMux);

    MoistureProbe moistureProbe4 = MoistureProbe(0, &adc_moisture_2, ADC_MOISTURE_2_MUX, &I2CMux);
    MoistureProbe moistureProbe5 = MoistureProbe(1, &adc_moisture_2, ADC_MOISTURE_2_MUX, &I2CMux);
    MoistureProbe moistureProbe6 = MoistureProbe(2, &adc_moisture_2, ADC_MOISTURE_2_MUX, &I2CMux);


    int previousPulseCount = 0;
    int previousPulseTime = 0;
    int16_t counterVal;
    int flowPPS;

};
extern Inputs inputs;

extern char logBuffer[TERMINAL_LOG_LENGTH + 1];
int serialLogger(const char* format, va_list args);

#endif // HAL_SEPTICSENSOR_H
