#ifndef MOD_INVERTER_H
#define MOD_INVERTER_H

#define INVERTER_BAUD 601
#define INVERTER_CONTROL_COMMAND_WORD 0
#define INVERTER_SPEED_SET_POINT_RPS 1
#define INVERTER_SPEED_REFERENCE_IDL 4
#define INVERTER_DRIVE_STATUS 5
#define INVERTER_OUTPUT_FREQUENCY 6
#define INVERTER_OUTPUT_CURRENT 7

#define INVERTER_OUTPUT_POWER 9
#define INVERTER_KWH_METER 31
#define INVERTER_INTERNAL_TEMPERATURE 38
#define INVERTER_SPEED_REFERENCE 39

#define INVERTER_OFF_TIME_COUNTDOWN 15
#define INVERTER_ON_TIME_COUNTDOWN 16

#ifndef MOD_INVERTER_ADDRESS
#define MOD_INVERTER_ADDRESS 5
#endif

#include <Arduino.h>
#include <ArduinoModbus.h>
#include "config.h"

class Mod_inverter {

    private:
        int id = MOD_INVERTER_ADDRESS;
        void writeRegister(int reg, int value);
        int readRegister(int reg);
        void writeCoil(int reg, bool value);

    public:
        // void getSensors(float *sensors);
        void init();
        // void resetNetworkSettings();
        // void updateNetworkSettings();
        // float getOutputFrequency(void);

};

#endif