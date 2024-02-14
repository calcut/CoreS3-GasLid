#ifndef RTOS_TASKS_H
#define RTOS_TASKS_H

#include "config.h"
#include "state_machine.h"
#include "esp_log.h"
#include "notecard_context.h"

#ifdef USE_GUI
#include "gui_helpers.h" 
#endif

void setupRtos(void);

void timeSyncNotecard(void * pvParameters);
void sendDataNotecard(void * pvParameters);
void serviceNotecard(void * pvParameters);
void serviceSerialInput(void * pvParameters);
void debugTask(void * pvParameters);
void runStateMachine(void * pvParameters);
void servicePID(void * pvParameters);
void serviceGUI(void * pvParameters);
void readFlowMeters(void *pvParameters);
void serviceGasCards(void *pvParameters);
void changeEnvVar(const char* key, const char* value);
void refreshEnvironment(void);
void gasSampleTimerCallback(TimerHandle_t xTimer);

#endif