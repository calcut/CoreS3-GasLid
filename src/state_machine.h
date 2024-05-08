#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "hal_septicsensor.h"
#include <QuickPID.h>
#include <unordered_map>

class StateMachine {
public:

    void init(void);
    void run();
    void sampleGasCards();
    void gasTransferMode();
    int getGasSampleDelay();
    void tunePID(void);
    void computePID();

    bool initComplete = false;

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
        {"GasPumpManualSpeed_pc", 50}, // used if flow meter is not available
        {"GasFlowMin", 100}, //Something is broken if below this
        {"GasFlowMax", 1200}, //Something is broken if above this
        {"WaterPumpTime_s", 10},
        {"WaterPumpInterval_s", 60},
        {"WaterPumpEnabled", 1},
        {"WaterPumpMoistureThreshold_pc", 60}
    };

    QuickPID* gasPID;
    float* gasPIDinput;
    float* gasPIDsetpoint;
    float gasPIDoutput = 0.0;
    bool gasPumpEnabled = false;
    bool gasSampleInProgress = false;

};

extern StateMachine stateMachine;

#endif // STATE_MACHINE_H
