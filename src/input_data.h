#ifndef INPUT_DATA_H
#define INPUTS_DATA_H

#include <unordered_map>

class InputData {
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
};
extern InputData inputData;

#endif // INPUT_DATA_H