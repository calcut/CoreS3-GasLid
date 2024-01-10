#include "outputs.h"

Outputs outputs;

void Outputs::init() {
    USBSerial.println("Outputs init");

    if (!MS1.begin()) {         // create with the default frequency 1.6KHz
        // if (!MS1.begin(1000)) {  // OR with a different frequency, say 1KHz
        USBSerial.println("Could not find Motor Shield 1. Check wiring.");
    }
    else USBSerial.println("Motor Shield 1 found.");

    if (!MS2.begin()) {         // create with the default frequency 1.6KHz
    USBSerial.println("Could not find Motor Shield 2. Check wiring.");
    }
    else USBSerial.println("Motor Shield 2 found.");

    if (!MS3.begin()) {         // create with the default frequency 1.6KHz
    USBSerial.println("Could not find Motor Shield 3. Check wiring.");
    }
    else USBSerial.println("Motor Shield 3 found.");

    setFlowValve(0, true);
    setFlowValve(1, true);
    setFlowValve(2, false);
    setFlowValve(3, false);
    setFlowValve(4, true);
    setGasPumpSpeed(0.5);

    if(!quadRelay.begin())
    USBSerial.println("Could not find Qwiic Relay. Check wiring.");
    else
    USBSerial.println("Qwiic Relay Found.");

    quadRelay.turnRelayOn(1); 
    delay(200);
    quadRelay.turnRelayOn(2); 
    delay(200);
    quadRelay.turnRelayOn(3); 
    delay(200);
    quadRelay.turnRelayOn(4); 
    delay(1000);
}

void Outputs::setFlowValve(int index, bool ValveState) {
    flowValves[index]->setSpeed(255);
    flowValves[index]->run(ValveState ? FORWARD : RELEASE);
}

void Outputs::setReturnValve(int index, bool ValveState) {
    returnValves[index]->setSpeed(255);
    returnValves[index]->run(ValveState ? FORWARD : RELEASE);
}

void Outputs::setGasPumpSpeed(float percent) {
    gasPump[0]->setSpeed(percent * 255);
    gasPump[0]->run(FORWARD);
}
