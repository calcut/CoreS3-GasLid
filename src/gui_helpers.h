#ifndef GUI_HELPERS_H
#define GUI_HELPERS_H

#include <lvgl.h>
#include <math.h>

#ifdef GASLID
#include <ui_gaslid/ui.h>
#endif
#ifdef SEPTICSENSOR
#include <ui_septicsensor/ui.h>
#endif

#include "gui_populate_widgets.h"
#include "rtos_tasks.h"

void setupGui(void);
void display_refresh_envVars();
void display_notecard_info(lv_timer_t * timer);
void display_sensor_info(lv_timer_t * timer);
void display_pid_info(lv_timer_t * timer);
void display_date_time_labels(lv_timer_t * timer);
void display_log(lv_timer_t * timer);
void display_pressure_enthalpy(lv_timer_t * timer);

void nc_info_screen_event_cb(lv_event_t * event);

void jacketslider_cb(lv_event_t * e);

//Timer to update date/time on screen
// void lv_timer_1s(lv_timer_t * timer);




#endif