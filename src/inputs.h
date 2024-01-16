#ifndef INPUTS_H
#define INPUTS_H

#include "mod_a1019.h"  //Temperature sensors
#include "mod_sdm120.h" //Power meter
#include "SparkFun_TCA9534.h" //GPIO Expander for physical Controls
#include <driver/pcnt.h> //ESP32 Pulse counter
#include <unordered_map>

class Inputs {
public:

    std::unordered_map<std::string, float> temperatureData = {
        {"Tc1", nan("0")},
        {"Tc2", nan("0")},
        {"Tc3", nan("0")},
        {"Tc4", nan("0")},
        {"Tc5", nan("0")},
    };

    std::unordered_map<std::string, float> pressureData = {
        {"Pr1", nan("0")},
        {"Pr2", nan("0")},
        {"Pr3", nan("0")},
        {"Pr4", nan("0")},
    };

    std::unordered_map<std::string, float> flowData = {
        {"WaterFlow", nan("0")},
        {"GasFlow", nan("0")},
    };

    std::unordered_map<std::string, float> powerData = {
        {"Power", nan("0")},
        {"Energy", nan("0")},
    };

    std::unordered_map<std::string, float> gasData = {
        {"CH4", nan("0")},
        {"CO2", nan("0")},
        {"N2O", nan("0")},
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
    Mod_sdm120 mod_sdm120;

private:
    int previousPulseCount = 0;
    int previousPulseTime = 0;
    int16_t counterVal;
    int flowPPS;
};
extern Inputs inputs;

#endif // INPUTS_H
