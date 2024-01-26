#ifndef GUI_HELPERS_H
#define GUI_HELPERS_H

#include <lvgl.h>
#include <ui.h>

#include "notecard_manager.h"
#include "state_machine.h"
#ifdef WOKWI
#include "hal_wokwi.h"
#else
#include "hal_coreS3.h"
#endif //for serialDisplay

void setupGui(void);
void display_notecard_info(lv_timer_t * timer);
void display_sensor_info(lv_timer_t * timer);
void display_pid_info(lv_timer_t * timer);
void display_date_time_labels(lv_timer_t * timer);
void display_log(lv_timer_t * timer);
void display_pressure_enthalpy(lv_timer_t * timer);

void nc_info_screen_event_cb(lv_event_t * event);

//Timer to update date/time on screen
// void lv_timer_1s(lv_timer_t * timer);




#endif