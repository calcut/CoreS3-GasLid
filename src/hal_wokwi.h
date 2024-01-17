#ifndef HAL_WOKWI_H
#define HAL_WOKWI_H

#include <M5Unified.h>
#include "config.h"
#include "esp_log.h"


#include <FFat.h>
#include <Wire.h>
#include <ArduinoModbus.h>

#ifndef TERMINAL_LOG_LENGTH
#define TERMINAL_LOG_LENGTH 512
#endif

// Sets up I2C, Serial, Display etc
void hal_setup(void);

#endif // HAL_WOKWI_H
