#ifndef HAL_CORES3_H
#define HAL_CORES3_H

#include <M5Unified.h>
#include "config.h"

#include "input_data.h"

#include <FFat.h>
#include <Wire.h>
#include <ArduinoModbus.h>

// OUTPUTS
#include <Adafruit_MotorShield.h>
#include <SparkFun_Qwiic_Relay.h>

// INPUTS
#include "mod_a1019.h"  //Temperature sensors
#include "mod_sdm120.h" //Power meter
#include "SparkFun_TCA9534.h" //GPIO Expander for physical Controls
#include <driver/pcnt.h> //ESP32 Pulse counter

#ifndef TERMINAL_LOG_LENGTH
#define TERMINAL_LOG_LENGTH 512
#endif

#define JACKET_HEATER_RELAY 1
#define WATER_PUMP_RELAY 2

// Sets up I2C, Serial, Display etc
void hal_setup(void);

//To set the system time from the on-board RTC chip
void setSystemTime();

//To set the on-board RTC chip from time obtained by notecard
void setRTC(time_t epoch_time, int UTC_offset_minutes);


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
    void enableWaterPump(bool enable);

private:
    Qwiic_Relay quadRelay = Qwiic_Relay(0x6C); // Alternate address 0x6C

    Adafruit_MotorShield MS1 = Adafruit_MotorShield(0x6F);
    Adafruit_MotorShield MS2 = Adafruit_MotorShield(0x6E);
    Adafruit_MotorShield MS3 = Adafruit_MotorShield(0x6D);

    Adafruit_DCMotor *flowValves[5] = {
        MS1.getMotor(1),
        MS1.getMotor(2),
        MS1.getMotor(3),
        MS1.getMotor(4),
        MS3.getMotor(1),
    };

    Adafruit_DCMotor *returnValves[5] = {
        MS2.getMotor(1),
        MS2.getMotor(2),
        MS2.getMotor(3),
        MS2.getMotor(4),
        MS3.getMotor(2),
    };

    Adafruit_DCMotor *gasPump[1] = {
        MS3.getMotor(3),
    };

};
extern Outputs outputs;

class Inputs {
public:

    void init(void);
    void serviceFlowMeters(void);
    void pollSensorData(void);
    void pollPhysicalControls(void);

private:
    void initFlowMeters(int pin);
    TCA9534 gpioExpander;
    Mod_a1019 mod_a1019;
    Mod_sdm120 mod_sdm120;

    int previousPulseCount = 0;
    int previousPulseTime = 0;
    int16_t counterVal;
    int flowPPS;
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

#endif // HAL_CORES3_H
