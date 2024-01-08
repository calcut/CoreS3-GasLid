#ifndef INPUTS_H
#define INPUTS_H

#include "mod_a1019.h"
#include "mod_evd.h"
#include "mod_sdm120.h"
#include "SparkFun_TCA9534.h"
#include <driver/pcnt.h> //ESP32 Pulse counter
#include <unordered_map>

class Inputs {
public:

    std::unordered_map<std::string, float> temperatureData = {
        {"Tr1_CompressorOut", nan("0")},
        {"Tr2_CondenserOut", nan("0")},
        {"Tr3_FlexStore", nan("0")},
        {"Tr4_Evaporator", nan("0")},
        {"Tr5_CompressorIn", nan("0")},
        {"Tw1_DHWReturn", nan("0")},
        {"Tw2_DHWFlow", nan("0")},
        {"Tw3_FlexStore", nan("0")},
        {"Tw4_SolarFlow", nan("0")},
        {"Tw5_SolarReturn", nan("0")},
        {"Ta1_EvaporatorIn", nan("0")},
        {"Ta2_EvaporatorOut", nan("0")}
    };

    std::unordered_map<std::string, float> pressureData = {
        {"Pr1_CompressorOut", nan("0")},
        {"Pr2_Evaporator", nan("0")},
        {"Pr3_CompressorIn", nan("0")}
    };

    std::unordered_map<std::string, float> flowData = {
        {"Fl1_DHW_lpm", nan("0")},
        {"Fl2_Solar", nan("0")}
    };

    std::unordered_map<std::string, float> powerData = {
        {"P1_Supply", nan("0")},
        {"P2_Compressor", nan("0")},
        {"P3_Fan", nan("0")}
    };

    std::unordered_map<std::string, float> speedData = {
        {"S1_Compressor", nan("0")},
        {"P2_Fan", nan("0")}
    };



    enum HandOffAuto {
        OFF,
        HAND,
        AUTO,
    };

    enum ManualState {
        CHARGING,
        DISCHARGING,
        DEFROST,
    };

    struct PhysicalControls{
        HandOffAuto handOffAuto;
        ManualState manualState;
    };

    void init(void);
    void initFlowMeters(int pin);
    void serviceFlowMeters(void);
    void pollSensorData(void);
    void pollPhysicalControls(void);
    PhysicalControls physicalControls;

    TCA9534 gpioExpander;
    Mod_a1019 mod_a1019;
    Mod_evd mod_evd;
    Mod_sdm120 mod_sdm120;

private:

    int previousPulseCount = 0;
    int previousPulseTime = 0;
    int16_t counterVal;
    int flowPPS;
};
extern Inputs inputs;

#endif // INPUTS_H
