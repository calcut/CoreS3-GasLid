#ifdef WOKWI
#include "hal_wokwi.h"
#else
#include "hal_coreS3.h"
#include "rtos_tasks.h"
#endif

void setup() {
    hal_setup();
#ifndef WOKWI
    setupRtos();
#endif
} 

void loop() {
    // Nothing here. All the work is done in the RTOS tasks
}
