#ifndef HAL_CORES3_H
#define HAL_CORES3_H

#include <M5Unified.h>
#include "config.h"

#include <FFat.h>
#include <Wire.h>
#include <ArduinoModbus.h>
#include <Adafruit_MotorShield.h>
#include <SparkFun_Qwiic_Relay.h>

#ifndef TERMINAL_LOG_LENGTH
#define TERMINAL_LOG_LENGTH 512
#endif

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
    Qwiic_Relay quadRelay = Qwiic_Relay(0x6C); // Alternate address 0x6C

    void init();
    void setFlowValve(int index, bool ValveState);
    void setReturnValve(int index, bool ValveState);
    void setGasPumpSpeed(float percent);

private:
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
