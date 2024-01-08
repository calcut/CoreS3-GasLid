#ifndef MOD_SDM120_H
#define MOD_SDM120_H

#ifndef MOD_SDM120_ADDRESS
#define MOD_SDM120_ADDRESS 1
#endif

#include <ArduinoModbus.h>

#define SDM120_VOLTAGE 0 //Volts
#define SDM120_CURRENT 6 //Amps
#define SDM120_ACTIVE_POWER 12 //Watts
#define SDM120_APPARENT_POWER 18 //VA
#define SDM120_REACTIVE_POWER 24 //VAr
#define SDM120_POWER_FACTOR 30 //0-1
#define SDM120_PHASE_ANGLE 36 //Degrees
#define SDM120_FREQUENCY 70 //Hz
#define SDM120_IMPORT_ACTIVE_ENERGY 72 //kWh
#define SDM120_EXPORT_ACTIVE_ENERGY 74 //kWh
#define SDM120_IMPORT_REACTIVE_ENERGY 76 //kVArh
#define SDM120_EXPORT_REACTIVE_ENERGY 78 //kVArh
#define SDM120_TOTAL_ACTIVE_ENERGY 342 //kWh
#define SDM120_TOTAL_REACTIVE_ENERGY 344 //kVArh


class Mod_sdm120 {

private:
    int id = MOD_SDM120_ADDRESS;

public:
    void init();
    // void readVoltage(float *voltage);
    float readRegister(int reg);
    void writeRegister(int reg, int value);
};

#endif