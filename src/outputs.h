#ifndef OUTPUTS_H
#define OUTPUTS_H

#include <Adafruit_MotorShield.h>
#include <SparkFun_Qwiic_Relay.h>

class Outputs {
public:

    enum ValveState {
        OPEN = 1,
        CLOSED = 0
    };

    void init();
    void setFlowValve(int index, bool ValveState);
    void setReturnValve(int index, bool ValveState);
    void setGasPumpSpeed(float percent);
};

extern Outputs outputs;

#endif // OUTPUTS_H