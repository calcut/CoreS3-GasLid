#ifndef INPUT_DATA_H
#define INPUTS_DATA_H

#include <unordered_map>

class InputData {
public:
    std::unordered_map<std::string, float> temperatureData = {
        {"ts1", nan("0")},
        {"ts2", nan("0")},
        {"ts3", nan("0")},
        {"tl1", nan("0")},
        {"tl2", nan("0")},
        {"tl3", nan("0")},
    };

    std::unordered_map<std::string, float> biofilterTemperatureData = {
        {"tb1", nan("0")},
        {"tb2", nan("0")},
        {"tb3", nan("0")},
        {"tb4", nan("0")},
        {"tb5", nan("0")},
        {"tb6", nan("0")},
        {"tb7", nan("0")},
        {"tb8", nan("0")},
    };
    // std::unordered_map<std::string, float> pressureData = {
    //     {"Pr1", nan("0")},
    //     {"Pr2", nan("0")},
    //     {"Pr3", nan("0")},
    //     {"Pr4", nan("0")},
    // };

    std::unordered_map<std::string, float> flowData = {
        {"WaterFlow", nan("0")},
        {"GasFlow", nan("0")},
    };

    std::unordered_map<std::string, float> powerData = {
        {"Power", nan("0")},
        {"Energy", nan("0")},
    };

    std::unordered_map<std::string, float> gasData = {
        {"gc0", nan("0")},
        {"gc1", nan("0")},
        {"gc2", nan("0")},
        {"gc3", nan("0")},
    };

    std::unordered_map<std::string, float> pHData = {
        {"pH1", nan("0")},
        {"pH2", nan("0")},
        {"pH3", nan("0")},
    };

    std::unordered_map<std::string, float> moistureData = {
        {"ms1", nan("0")},
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

};
extern InputData inputData;

#endif // INPUT_DATA_H