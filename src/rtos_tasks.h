#ifndef RTOS_TASKS_H
#define RTOS_TASKS_H

#include "config.h"
#include "hal_coreS3.h"
#include "state_machine.h"

#ifdef USE_NOTECARD
#include "notecard_context.h"
#endif

#ifdef USE_GUI
#include "gui_helpers.h" 
#endif

void setupRtos(void);

void timeSyncNotecard(void * pvParameters);
void serviceNotecard(void * pvParameters);
void debugTask(void * pvParameters);
void runStateMachine(void * pvParameters);
void serviceGUI(void * pvParameters);
void readFlowMeters(void *pvParameters);

#endif