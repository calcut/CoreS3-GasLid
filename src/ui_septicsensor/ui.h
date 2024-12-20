// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SepticSensor_SLS_Project

#ifndef _SEPTICSENSOR_SLS_PROJECT_UI_H
#define _SEPTICSENSOR_SLS_PROJECT_UI_H

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
void ui_event_s0_Label01( lv_event_t * e);
extern lv_obj_t *ui_s0_Label01;
void ui_event_s0_Label02( lv_event_t * e);
extern lv_obj_t *ui_s0_Label02;
void ui_event_s0_Label03( lv_event_t * e);
extern lv_obj_t *ui_s0_Label03;
void ui_event_s0_Label04( lv_event_t * e);
extern lv_obj_t *ui_s0_Label04;
void ui_event_s0_Label05( lv_event_t * e);
extern lv_obj_t *ui_s0_Label05;
void ui_event_s0_Label06( lv_event_t * e);
extern lv_obj_t *ui_s0_Label06;
void ui_event_s0_Label08( lv_event_t * e);
extern lv_obj_t *ui_s0_Label08;
void ui_event_s0_Label07( lv_event_t * e);
extern lv_obj_t *ui_s0_Label07;
void ui_event_s0_Label09( lv_event_t * e);
extern lv_obj_t *ui_s0_Label09;
// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t *ui_Screen1;
extern lv_obj_t *ui_s1_Header;
extern lv_obj_t *ui_s1_headerTitle;
extern lv_obj_t *ui_s1_headerTime;
extern lv_obj_t *ui_s1_backLabel;
void ui_event_s1_backButton( lv_event_t * e);
extern lv_obj_t *ui_s1_backButton;
void ui_event_s1_tempSlider1( lv_event_t * e);
extern lv_obj_t *ui_s1_tempSlider1;
extern lv_obj_t *ui_s1_indexLabel1;
extern lv_obj_t *ui_s1_tempLabel1;
extern lv_obj_t *ui_s1_indexLabel2;
void ui_event_s1_tempSlider2( lv_event_t * e);
extern lv_obj_t *ui_s1_tempSlider2;
extern lv_obj_t *ui_s1_tempLabel2;
void ui_event_s1_tempSlider3( lv_event_t * e);
extern lv_obj_t *ui_s1_tempSlider3;
extern lv_obj_t *ui_s1_indexLabel3;
extern lv_obj_t *ui_s1_tempLabel3;
// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
extern lv_obj_t *ui_Screen2;
extern lv_obj_t *ui_s2_Header;
extern lv_obj_t *ui_s2_headerTime;
extern lv_obj_t *ui_s2_backLabel;
extern lv_obj_t *ui_s2_headerTitle;
void ui_event_s2_backButton( lv_event_t * e);
extern lv_obj_t *ui_s2_backButton;
extern lv_obj_t *ui_s2_label1;
extern lv_obj_t *ui_s2_Keyboard;
extern lv_obj_t *ui_s2_Time1;
extern lv_obj_t *ui_s2_Time2;
extern lv_obj_t *ui_s2_Time3;
extern lv_obj_t *ui_s2_Time4;
extern lv_obj_t *ui_s2_label2;
extern lv_obj_t *ui_s2_label3;
extern lv_obj_t *ui_s2_label4;
extern lv_obj_t *ui_s2_GoButton;
extern lv_obj_t *ui_s2_Label_Go;
extern lv_obj_t *ui_s2_StopButton;
extern lv_obj_t *ui_s2_Label_Stop;
// SCREEN: ui_Screen3
void ui_Screen3_screen_init(void);
extern lv_obj_t *ui_Screen3;
extern lv_obj_t *ui_s3_Header;
extern lv_obj_t *ui_s3_backLabel;
extern lv_obj_t *ui_s3_headerTitle;
extern lv_obj_t *ui_s3_headerTime;
extern lv_obj_t *ui_s3_Bar1;
extern lv_obj_t *ui_s3_Bar2;
extern lv_obj_t *ui_s3_Bar3;
extern lv_obj_t *ui_s3_Bar4;
extern lv_obj_t *ui_s3_LabelRSSI;
extern lv_obj_t *ui_s3_LabelConnected;
extern lv_obj_t *ui_s3_LabelBand;
extern lv_obj_t *ui_s3_LabelRat;
extern lv_obj_t *ui_s3_LabelSerial;
extern lv_obj_t *ui_s3_LabelSyncStatus;
extern lv_obj_t *ui_s3_LabelDevice;
extern lv_obj_t *ui_s3_LabelHubStatus;
extern lv_obj_t *ui_s3_TextAreaHubStatus;
extern lv_obj_t *ui_s3_TextAreaSyncStatus;
extern lv_obj_t *ui_s3_Button_Refresh;
extern lv_obj_t *ui_s3_Label_Refresh;
void ui_event_s3_backButton( lv_event_t * e);
extern lv_obj_t *ui_s3_backButton;
// SCREEN: ui_Screen4
void ui_Screen4_screen_init(void);
extern lv_obj_t *ui_Screen4;
extern lv_obj_t *ui_s4_image;
extern lv_obj_t *ui_s4_Header;
extern lv_obj_t *ui_s4_backLabel;
extern lv_obj_t *ui_s4_headerTitle;
extern lv_obj_t *ui_s4_headerTime;
extern lv_obj_t *ui_s4_Ki_val;
extern lv_obj_t *ui_s4_Kp_val;
extern lv_obj_t *ui_s4_Kd_val;
extern lv_obj_t *ui_s4_Setpoint_val;
extern lv_obj_t *ui_s4_Error_val;
extern lv_obj_t *ui_s4_Input_val;
extern lv_obj_t *ui_s4_Iterm_val;
extern lv_obj_t *ui_s4_Output_val;
extern lv_obj_t *ui_s4_Pterm_val;
extern lv_obj_t *ui_s4_Dterm_val;
void ui_event_s4_backButton( lv_event_t * e);
extern lv_obj_t *ui_s4_backButton;
// SCREEN: ui_Screen5
void ui_Screen5_screen_init(void);
extern lv_obj_t *ui_Screen5;
extern lv_obj_t *ui_s5_Header;
extern lv_obj_t *ui_s5_backLabel;
extern lv_obj_t *ui_s5_headerTitle;
extern lv_obj_t *ui_s5_headerTime;
extern lv_obj_t *ui_s5_TextAreaLog;
void ui_event_s5_backButton( lv_event_t * e);
extern lv_obj_t *ui_s5_backButton;
// SCREEN: ui_Screen6
void ui_Screen6_screen_init(void);
extern lv_obj_t *ui_Screen6;
extern lv_obj_t *ui_s6_Chart;
extern lv_obj_t *ui_s6_Header;
extern lv_obj_t *ui_s6_backLabel;
extern lv_obj_t *ui_s6_headerTitle;
extern lv_obj_t *ui_s6_headerTime;
void ui_event_s6_backButton( lv_event_t * e);
extern lv_obj_t *ui_s6_backButton;
// SCREEN: ui_Screen7
void ui_Screen7_screen_init(void);
extern lv_obj_t *ui_Screen7;
extern lv_obj_t *ui_s7_Header;
extern lv_obj_t *ui_s7_backLabel;
extern lv_obj_t *ui_s7_headerTitle;
extern lv_obj_t *ui_s7_headerTime;
void ui_event_s7_backButton( lv_event_t * e);
extern lv_obj_t *ui_s7_backButton;
extern lv_obj_t *ui_s7_panel1;
extern lv_obj_t *ui_s7_bar1;
extern lv_obj_t *ui_s7_value1;
extern lv_obj_t *ui_s7_name1;
// SCREEN: ui_Screen8
void ui_Screen8_screen_init(void);
extern lv_obj_t *ui_Screen8;
extern lv_obj_t *ui_s8_Header;
extern lv_obj_t *ui_s8_backLabel;
extern lv_obj_t *ui_s8_headerTitle;
extern lv_obj_t *ui_s8_headerTime;
void ui_event_s8_backButton( lv_event_t * e);
extern lv_obj_t *ui_s8_backButton;
// SCREEN: ui_Screen9
void ui_Screen9_screen_init(void);
extern lv_obj_t *ui_Screen9;
extern lv_obj_t *ui_s9_Header;
extern lv_obj_t *ui_s9_backLabel;
extern lv_obj_t *ui_s9_headerTitle;
extern lv_obj_t *ui_s9_headerTime;
void ui_event_s9_backButton( lv_event_t * e);
extern lv_obj_t *ui_s9_backButton;
extern lv_obj_t *ui____initial_actions0;

LV_IMG_DECLARE( ui_img_pid_widgets_png);   // assets/PID Widgets.png

LV_FONT_DECLARE( ui_font_Number);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
