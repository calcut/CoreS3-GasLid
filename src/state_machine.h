#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "hal_septicsensor.h"
#include <unordered_map>

class StateMachine {
public:

    enum State {
        STANDBY,
        CHARGING,
        DISCHARGING, 
        DEFROST,
        ERROR
    };

    void init(void);
    void run();
    void sampleGasCards();
    int getGasSampleDelay();
    void tunePID(void);
    void computePID();


    bool initComplete = false;


    State currentState;
    State previousState;
    // Inputs::SensorData sensorData;
    // Inputs::SensorData sensorDataLimitsMax;
    // Inputs::SensorData sensorDataLimitsMin;

    float* demandSensor;
    float* defrostSensor;
    float* flexStoreSensor;

    std::unordered_map<std::string, float> envVars = {
        {"gasSampleNow", 0},
        {"gasSampleStop", 0},
        {"gasPurgeTime_s", 10},
        {"gasPumpTime_s", 10},
        {"gasSampleChannels", 3},
        {"sampleTime1_hour", 12},
        {"sampleTime1_min", 51},
        {"sampleTime2_hour", 13},
        {"sampleTime2_min", 30},
        {"sampleTime3_hour", 15},
        {"sampleTime3_min", 0},
        {"sampleTime4_hour", 15},
        {"sampleTime4_min", 0},
        {"targetTempTank1", 30},
        {"targetTempTank2", 30},
        {"targetTempTank3", 30},
        {"jacketHeaterHysteresis", 1},
        {"GasFlowSetpoint", 1000}, // mL/minute
        {"GasFlowMin", 100}, //Something is broken if below this
        {"GasFlowMax", 1200}, //Something is broken if above this
    };

    bool gasPumpEnabled = false;

};

extern StateMachine stateMachine;

#endif // STATE_MACHINE_H
