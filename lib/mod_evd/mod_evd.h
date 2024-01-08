#ifndef MOD_EVD_H
#define MOD_EVD_H

#define EVD_S1_READ 0
#define EVD_S2_READ 1
#define EVD_S3_READ 2
#define EVD_S4_READ 3
#define EVD_FIRMWARE_VERSION 24
#define EVD_NETWORK_SETTINGS 201
#define EVD_NETWORK_ADDRESS 138

#define EVD_S1_ENABLE 15
#define EVD_S2_ENABLE 16
#define EVD_S3_ENABLE 17
#define EVD_S4_ENABLE 18

#define EVD_S1_CONFIG 143
#define EVD_S2_CONFIG 144
#define EVD_S3_CONFIG 146
#define EVD_S4_CONFIG 147

#define EVD_KP 47
#define EVD_KI 165
#define EVD_KD 48
#define EVD_SH_SETPOINT 49

#define EVD_POWER_SUPPLY_MODE 46
#define EVD_REFRIGERANT_TYPE 140
#define EVD_MAIN_CONTROL 142

#ifndef MOD_EVD_ADDRESS
#define MOD_EVD_ADDRESS 198
#endif

#include <Arduino.h>
#include <ArduinoModbus.h>
#include "config.h"

class Mod_evd {

    private:
        int id = MOD_EVD_ADDRESS;
        void writeRegister(int reg, int value);
        int readRegister(int reg);
        void writeCoil(int reg, bool value);

    public:
        void getSensors(float *sensors);
        void init();
        void resetNetworkSettings();
        void updateNetworkSettings();
};

#endif