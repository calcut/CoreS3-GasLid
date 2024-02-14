#ifdef WOKWI
#include "hal_wokwi.h"
#else
#include "hal_coreS3.h"
#endif

#include "rtos_tasks.h"

void setup() {
    hal_setup();
    setupRtos();
} 

void loop() {
// Nothing here. All the work is done in the RTOS tasks

#ifdef WOKWI
    // This gives the WOKWI simulator a chance to run
    delay(10);
    vTaskDelay(5 / portTICK_PERIOD_MS);

#endif

}
