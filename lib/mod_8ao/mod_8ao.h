#ifndef MOD_8AO_H
#define MOD_8AO_H

#define MOD_8AO_VERSION 0
#define MOD_8AO_WATCHDOG 8

#define MOD_8AO_OUTPUT1 52
#define MOD_8AO_DEFAULT_OUTPUT1 60
#define MOD_8AO_OUTPUT_TYPE1 68

#ifndef MOD_8AO_ADDRESS
#define MOD_8AO_ADDRESS 3
#endif

#include <Arduino.h>
#include <ArduinoModbus.h>

enum OutputType {
    OUTPUT_DISABLED = 0,
    VOLTAGE = 1,
    CURRENT_0_20MA = 2,
    CURRENT_4_20MA = 3 //Not supported yet
};

class Mod_8AO {

    private:
        int id = MOD_8AO_ADDRESS;
        
        OutputType output_types[8] = {OUTPUT_DISABLED,
                                    OUTPUT_DISABLED,
                                    OUTPUT_DISABLED,
                                    OUTPUT_DISABLED,
                                    OUTPUT_DISABLED,
                                    OUTPUT_DISABLED,
                                    OUTPUT_DISABLED,   
                                    OUTPUT_DISABLED};

    public:

        void init();
        void setOutputVoltage(int output, int mVolts);
        void setOutputVoltageDefault(int output, int mVolts);
        void setOutputCurrent(int output, int uAmps);
        void setOutputCurrentDefault(int output, int uAmps);

        void setOutputType(int output, OutputType type);
        // Caution, for the change to take effect,
        // you must also set the jumper inside the module.

        void setWatchdog(int16_t watchdog_ms);
        int16_t getWatchdog();
};

#endif