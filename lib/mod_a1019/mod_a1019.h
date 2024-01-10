#ifndef MOD_A1019_H
#define MOD_A1019_H

#define MODULE_NAME_ADDR 210

#ifndef MOD_A1019_ADDRESS
#define MOD_A1019_ADDRESS 0
#endif

#include <Arduino.h>
#include <ArduinoModbus.h>

class Mod_a1019 {

    private:
        int id = MOD_A1019_ADDRESS;

    public:

        enum channelType {
            TYPE_THERMOCOUPLE_K = 3,
            TYPE_0_20MA = 1,
            TYPE_4_20MA = 0
        };

        void readTC_float(float_t *tc);
        void readTC_int(int32_t *tc);
        void readTC_int_decimal(int32_t *tc);
        void setTypeTC();
        void setType(int channel, channelType type);
        void getType();
        void init();
};

#endif