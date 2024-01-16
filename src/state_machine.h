#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "outputs.h"
#include "inputs.h"
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

    bool enabled = false;


    State currentState;
    State previousState;
    // Inputs::SensorData sensorData;
    // Inputs::SensorData sensorDataLimitsMax;
    // Inputs::SensorData sensorDataLimitsMin;

    float* demandSensor;
    float* defrostSensor;
    float* flexStoreSensor;

    std::unordered_map<std::string, int> envVars = {
        {"gasPurgeTime_s", 10},
        {"gasPumpTime_s", 10},
        {"gasPumpSpeed_pc", 50},
        {"gasSampleChannels", 4},
        {"sampleTime1_hour", 12},
        {"sampleTime1_minute", 12},
        {"sampleTime2_hour", 12},
        {"sampleTime2_minute", 12},
        {"sampleTime3_hour", 12},
        {"sampleTime3_minute", 12},
        
    };

    // This will be equal to either flexStoreLow or flexStoreHigh
    // Depending on whether the system is charging or discharging
    float flexStoreThreshold = 20.0;

    QuickPID* compressorPID;
    float* compressorPIDinput;
    float* compressorPIDsetpoint;
    float compressorPIDoutput = 0.0;


private:

    float defrostTimer = 0.0;

    bool checkLimits(void);
    void standbyState(void);
    void dischargingState(void);
    void chargingState(void);
    void defrostState(void);
    void tunePID(void);
    void compressorManualSpeed(float speed_percent);
};

extern StateMachine stateMachine;

#endif // STATE_MACHINE_H
