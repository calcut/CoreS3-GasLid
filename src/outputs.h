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

    Qwiic_Relay quadRelay = Qwiic_Relay(0x6D); // Alternate address 0x6C

    Adafruit_MotorShield MS1 = Adafruit_MotorShield(0x6F);
    Adafruit_MotorShield MS2 = Adafruit_MotorShield(0x6E);
    Adafruit_MotorShield MS3 = Adafruit_MotorShield(0x6D);

    Adafruit_DCMotor *flowValves[5] = {
        MS1.getMotor(1),
        MS1.getMotor(2),
        MS1.getMotor(3),
        MS1.getMotor(4),
        MS3.getMotor(1),
    };

    Adafruit_DCMotor *returnValves[5] = {
        MS2.getMotor(1),
        MS2.getMotor(2),
        MS2.getMotor(3),
        MS2.getMotor(4),
        MS3.getMotor(2),
    };

    Adafruit_DCMotor *gasPump[1] = {
        MS3.getMotor(3),
    };

    void init();
    void setFlowValve(int index, bool ValveState);
    void setReturnValve(int index, bool ValveState);
    void setGasPumpSpeed(float percent);
};

extern Outputs outputs;

#endif // OUTPUTS_H