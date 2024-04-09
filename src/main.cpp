#include "hal_septicsensor.h"
#include "rtos_tasks.h"

void setup() {
    hal_setup();
    setupRtos();
    vTaskStartScheduler();
} 

void loop() {
// Nothing here. All the work is done in the RTOS tasks
}
