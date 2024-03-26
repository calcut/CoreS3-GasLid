#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "hal_gaslid.h"
#include <QuickPID.h>
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
        {"gasPID_P", 0.01},
        {"gasPID_I", 0.01},
        {"gasPID_D", 0.001},
        {"GasFlowSetpoint", 1000}, // mL/minute
        {"GasFlowManualSpeed", 50}, // Percent, used if PID not available
        {"GasFlowMin", 100}, //Something is broken if below this
        {"GasFlowMax", 1200}, //Something is broken if above this
    };

    // This will be equal to either flexStoreLow or flexStoreHigh
    // Depending on whether the system is charging or discharging
    float flexStoreThreshold = 20.0;

    QuickPID* gasPID;
    float* gasPIDinput;
    float* gasPIDsetpoint;
    float gasPIDoutput = 0.0;
    bool gasPumpEnabled = false;

};

extern StateMachine stateMachine;

#endif // STATE_MACHINE_H
