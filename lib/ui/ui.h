// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: CoreS3_SLS_Project

#ifndef _CORES3_SLS_PROJECT_UI_H
#define _CORES3_SLS_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
  #if __has_include("lvgl.h")
    #include "lvgl.h"
  #elif __has_include("lvgl/lvgl.h")
    #include "lvgl/lvgl.h"
  #else
    #include "lvgl.h"
  #endif
#else
  #include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "ui_events.h"
// SCREEN: ui_Screen0
void ui_Screen0_screen_init(void);
extern lv_obj_t *ui_Screen0;
void ui_event_Label01( lv_event_t * e);
extern lv_obj_t *ui_Label01;
void ui_event_Label02( lv_event_t * e);
extern lv_obj_t *ui_Label02;
void ui_event_Label03( lv_event_t * e);
extern lv_obj_t *ui_Label03;
void ui_event_Label4( lv_event_t * e);
extern lv_obj_t *ui_Label4;
void ui_event_Label05( lv_event_t * e);
extern lv_obj_t *ui_Label05;
void ui_event_Label06( lv_event_t * e);
extern lv_obj_t *ui_Label06;
void ui_event_Label08( lv_event_t * e);
extern lv_obj_t *ui_Label08;
void ui_event_Label07( lv_event_t * e);
extern lv_obj_t *ui_Label07;
void ui_event_Label09( lv_event_t * e);
extern lv_obj_t *ui_Label09;
// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t *ui_Screen1;
extern lv_obj_t *ui_Header1;
extern lv_obj_t *ui_BackLabel01;
extern lv_obj_t *ui_Header_Title1;
void ui_event_Button1( lv_event_t * e);
extern lv_obj_t *ui_Button1;
void ui_event_Slider1_temp1( lv_event_t * e);
extern lv_obj_t *ui_Slider1_temp1;
extern lv_obj_t *ui_Label1_tank1;
extern lv_obj_t *ui_Label1_temp1;
extern lv_obj_t *ui_Label1_tank2;
void ui_event_Slider1_temp2( lv_event_t * e);
extern lv_obj_t *ui_Slider1_temp2;
extern lv_obj_t *ui_Label1_temp2;
void ui_event_Slider1_temp3( lv_event_t * e);
extern lv_obj_t *ui_Slider1_temp3;
extern lv_obj_t *ui_Label1_tank3;
extern lv_obj_t *ui_Label1_temp3;
// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
extern lv_obj_t *ui_Screen2;
extern lv_obj_t *ui_Header2;
extern lv_obj_t *ui_BackLabel02;
extern lv_obj_t *ui_Header_Title2;
void ui_event_Button2( lv_event_t * e);
extern lv_obj_t *ui_Button2;
extern lv_obj_t *ui_Roller1;
// SCREEN: ui_Screen3
void ui_Screen3_screen_init(void);
extern lv_obj_t *ui_Screen3;
extern lv_obj_t *ui_Header3;
extern lv_obj_t *ui_BackLabel03;
extern lv_obj_t *ui_Header_Title3;
extern lv_obj_t *ui_Header_Time3;
extern lv_obj_t *ui_Bar1;
extern lv_obj_t *ui_Bar2;
extern lv_obj_t *ui_Bar3;
extern lv_obj_t *ui_Bar4;
extern lv_obj_t *ui_LabelRSSI;
extern lv_obj_t *ui_LabelConnected;
extern lv_obj_t *ui_LabelBand;
extern lv_obj_t *ui_LabelRat;
extern lv_obj_t *ui_LabelSerial;
extern lv_obj_t *ui_LabelSyncStatus;
extern lv_obj_t *ui_LabelDevice;
extern lv_obj_t *ui_LabelHubStatus;
extern lv_obj_t *ui_TextAreaHubStatus;
extern lv_obj_t *ui_TextAreaSyncStatus;
extern lv_obj_t *ui_Button3_Refresh;
extern lv_obj_t *ui_Label3_Refresh;
void ui_event_Button3( lv_event_t * e);
extern lv_obj_t *ui_Button3;
// SCREEN: ui_Screen4
void ui_Screen4_screen_init(void);
extern lv_obj_t *ui_Screen4;
extern lv_obj_t *ui_Image1;
extern lv_obj_t *ui_Header4;
extern lv_obj_t *ui_BackLabel04;
extern lv_obj_t *ui_Header_Title4;
extern lv_obj_t *ui_Label4_Ki_val;
extern lv_obj_t *ui_Label4_Kp_val;
extern lv_obj_t *ui_Label4_Kd_val;
extern lv_obj_t *ui_Label4_Setpoint_val;
extern lv_obj_t *ui_Label4_Error_val;
extern lv_obj_t *ui_Label4_Input_val;
extern lv_obj_t *ui_Label4_Iterm_val;
extern lv_obj_t *ui_Label4_Output_val;
extern lv_obj_t *ui_Label4_Pterm_val;
extern lv_obj_t *ui_Label4_Dterm_val;
void ui_event_Button4( lv_event_t * e);
extern lv_obj_t *ui_Button4;
// SCREEN: ui_Screen5
void ui_Screen5_screen_init(void);
extern lv_obj_t *ui_Screen5;
extern lv_obj_t *ui_Header5;
extern lv_obj_t *ui_BackLabel05;
extern lv_obj_t *ui_Header_Title5;
extern lv_obj_t *ui_TextAreaLog;
void ui_event_Button5( lv_event_t * e);
extern lv_obj_t *ui_Button5;
// SCREEN: ui_Screen6
void ui_Screen6_screen_init(void);
extern lv_obj_t *ui_Screen6;
extern lv_obj_t *ui_Chart1;
extern lv_obj_t *ui_Header6;
extern lv_obj_t *ui_BackLabel6;
extern lv_obj_t *ui_Header_Title6;
void ui_event_Button6( lv_event_t * e);
extern lv_obj_t *ui_Button6;
// SCREEN: ui_Screen7
void ui_Screen7_screen_init(void);
extern lv_obj_t *ui_Screen7;
extern lv_obj_t *ui_Header7;
extern lv_obj_t *ui_BackLabel7;
extern lv_obj_t *ui_Header_Title7;
void ui_event_Button7( lv_event_t * e);
extern lv_obj_t *ui_Button7;
extern lv_obj_t *ui_s7_panel1;
extern lv_obj_t *ui_s7_bar1;
extern lv_obj_t *ui_s7_value1;
extern lv_obj_t *ui_s7_name1;
// SCREEN: ui_Screen8
void ui_Screen8_screen_init(void);
extern lv_obj_t *ui_Screen8;
extern lv_obj_t *ui_Header8;
extern lv_obj_t *ui_BackLabel8;
extern lv_obj_t *ui_Header_Title8;
void ui_event_Button8( lv_event_t * e);
extern lv_obj_t *ui_Button8;
// SCREEN: ui_Screen9
void ui_Screen9_screen_init(void);
extern lv_obj_t *ui_Screen9;
extern lv_obj_t *ui_Header9;
extern lv_obj_t *ui_BackLabel9;
extern lv_obj_t *ui_Header_Title9;
void ui_event_Button9( lv_event_t * e);
extern lv_obj_t *ui_Button9;
extern lv_obj_t *ui____initial_actions0;

LV_IMG_DECLARE( ui_img_pid_widgets_png);   // assets/PID Widgets.png

LV_FONT_DECLARE( ui_font_Number);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
