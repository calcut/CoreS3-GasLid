#ifndef HAL_WOKWI_H
#define HAL_WOKWI_H

#include <M5Unified.h>
#include "config.h"
#include <ArduinoModbus.h>
#include <Wire.h>
#include "RTClib.h"

#include "input_data.h"

// Sets up I2C, Serial, Display etc
void hal_setup(void);
void setSystemTime(void);

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
    void enableJacketHeater(bool enable);
    bool getJacketHeater(void);
    void enableWaterPump(bool enable);
};

extern Outputs outputs;

class Inputs {
public:

    void init(void);
    void serviceFlowMeters(void);
    void pollSensorData(void);
    void pollPhysicalControls(void);
};
extern Inputs inputs;

class SerialDisplay : public HWCDC
//https://stackoverflow.com/questions/60972073/customizing-the-standard-serial-print-functions-in-arduino
{
    using HWCDC::HWCDC; // Inherit constructors
    public:
        size_t write(const uint8_t *buffer, size_t size) override;   // Overriding base functionality
        char logBuffer[TERMINAL_LOG_LENGTH + 1];
};
extern SerialDisplay serialDisplay;

#endif // HAL_WOKWI_H
