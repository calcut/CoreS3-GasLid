#ifndef INPUT_DATA_H
#define INPUTS_DATA_H

#include <unordered_map>
#include <math.h>

class InputData {
public:
    std::unordered_map<std::string, float> temperatureData = {
        {"ts1", NAN},
        {"ts2", NAN},
        {"ts3", NAN},
        {"tl1", NAN},
        {"tl2", NAN},
        {"tl3", NAN},
    };

    // std::unordered_map<std::string, float> pressureData = {
    //     {"Pr1", NAN},
    //     {"Pr2", NAN},
    //     {"Pr3", NAN},
    //     {"Pr4", NAN},
    // };

    std::unordered_map<std::string, float> flowData = {
        {"WaterFlow", NAN},
        {"GasFlow", NAN},
    };

    std::unordered_map<std::string, float> powerData = {
        {"Power", NAN},
        {"Energy", NAN},
    };

    std::unordered_map<std::string, float> gasData = {
        {"gc1", NAN},
        {"gc2", NAN},
        {"gc3", NAN},
    };

    std::unordered_map<std::string, float> pHData = {
        {"pH1", NAN},
        {"pH2", NAN},
        {"pH3", NAN},
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