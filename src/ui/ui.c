// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SepticSensor_SLS_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Screen0
void ui_Screen0_screen_init(void);
lv_obj_t *ui_Screen0;
void ui_event_s0_Label01( lv_event_t * e);
lv_obj_t *ui_s0_Label01;
void ui_event_s0_Label02( lv_event_t * e);
lv_obj_t *ui_s0_Label02;
void ui_event_s0_Label03( lv_event_t * e);
lv_obj_t *ui_s0_Label03;
void ui_event_s0_Label04( lv_event_t * e);
lv_obj_t *ui_s0_Label04;
void ui_event_s0_Label05( lv_event_t * e);
lv_obj_t *ui_s0_Label05;
void ui_event_s0_Label06( lv_event_t * e);
lv_obj_t *ui_s0_Label06;
void ui_event_s0_Label08( lv_event_t * e);
lv_obj_t *ui_s0_Label08;
void ui_event_s0_Label07( lv_event_t * e);
lv_obj_t *ui_s0_Label07;
void ui_event_s0_Label09( lv_event_t * e);
lv_obj_t *ui_s0_Label09;


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t *ui_Screen1;
lv_obj_t *ui_s1_Header;
lv_obj_t *ui_s1_headerTitle;
lv_obj_t *ui_s1_headerTime;
lv_obj_t *ui_s1_backLabel;
void ui_event_s1_backButton( lv_event_t * e);
lv_obj_t *ui_s1_backButton;
void ui_event_s1_tempSlider1( lv_event_t * e);
lv_obj_t *ui_s1_tempSlider1;
lv_obj_t *ui_s1_indexLabel1;
lv_obj_t *ui_s1_tempLabel1;
lv_obj_t *ui_s1_indexLabel2;
void ui_event_s1_tempSlider2( lv_event_t * e);
lv_obj_t *ui_s1_tempSlider2;
lv_obj_t *ui_s1_tempLabel2;
void ui_event_s1_tempSlider3( lv_event_t * e);
lv_obj_t *ui_s1_tempSlider3;
lv_obj_t *ui_s1_indexLabel3;
lv_obj_t *ui_s1_tempLabel3;


// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
lv_obj_t *ui_Screen2;
lv_obj_t *ui_s2_Header;
lv_obj_t *ui_s2_headerTime;
lv_obj_t *ui_s2_backLabel;
lv_obj_t *ui_s2_headerTitle;
void ui_event_s2_backButton( lv_event_t * e);
lv_obj_t *ui_s2_backButton;
lv_obj_t *ui_s2_label1;
lv_obj_t *ui_s2_Keyboard;
lv_obj_t *ui_s2_Time1;
lv_obj_t *ui_s2_Time2;
lv_obj_t *ui_s2_Time3;
lv_obj_t *ui_s2_Time4;
lv_obj_t *ui_s2_label2;
lv_obj_t *ui_s2_label3;
lv_obj_t *ui_s2_label4;
lv_obj_t *ui_s2_GoButton;
lv_obj_t *ui_s2_Label_Go;
lv_obj_t *ui_s2_StopButton;
lv_obj_t *ui_s2_Label_Stop;


// SCREEN: ui_Screen3
void ui_Screen3_screen_init(void);
lv_obj_t *ui_Screen3;
lv_obj_t *ui_s3_Header;
lv_obj_t *ui_s3_backLabel;
lv_obj_t *ui_s3_headerTitle;
lv_obj_t *ui_s3_headerTime;
lv_obj_t *ui_s3_Bar1;
lv_obj_t *ui_s3_Bar2;
lv_obj_t *ui_s3_Bar3;
lv_obj_t *ui_s3_Bar4;
lv_obj_t *ui_s3_LabelRSSI;
lv_obj_t *ui_s3_LabelConnected;
lv_obj_t *ui_s3_LabelBand;
lv_obj_t *ui_s3_LabelRat;
lv_obj_t *ui_s3_LabelSerial;
lv_obj_t *ui_s3_LabelSyncStatus;
lv_obj_t *ui_s3_LabelDevice;
lv_obj_t *ui_s3_LabelHubStatus;
lv_obj_t *ui_s3_TextAreaHubStatus;
lv_obj_t *ui_s3_TextAreaSyncStatus;
lv_obj_t *ui_s3_Button_Refresh;
lv_obj_t *ui_s3_Label_Refresh;
void ui_event_s3_backButton( lv_event_t * e);
lv_obj_t *ui_s3_backButton;


// SCREEN: ui_Screen4
void ui_Screen4_screen_init(void);
lv_obj_t *ui_Screen4;
lv_obj_t *ui_s4_image;
lv_obj_t *ui_s4_Header;
lv_obj_t *ui_s4_backLabel;
lv_obj_t *ui_s4_headerTitle;
lv_obj_t *ui_s4_headerTime;
lv_obj_t *ui_s4_Ki_val;
lv_obj_t *ui_s4_Kp_val;
lv_obj_t *ui_s4_Kd_val;
lv_obj_t *ui_s4_Setpoint_val;
lv_obj_t *ui_s4_Error_val;
lv_obj_t *ui_s4_Input_val;
lv_obj_t *ui_s4_Iterm_val;
lv_obj_t *ui_s4_Output_val;
lv_obj_t *ui_s4_Pterm_val;
lv_obj_t *ui_s4_Dterm_val;
void ui_event_s4_backButton( lv_event_t * e);
lv_obj_t *ui_s4_backButton;


// SCREEN: ui_Screen5
void ui_Screen5_screen_init(void);
lv_obj_t *ui_Screen5;
lv_obj_t *ui_s5_Header;
lv_obj_t *ui_s5_backLabel;
lv_obj_t *ui_s5_headerTitle;
lv_obj_t *ui_s5_headerTime;
lv_obj_t *ui_s5_TextAreaLog;
void ui_event_s5_backButton( lv_event_t * e);
lv_obj_t *ui_s5_backButton;


// SCREEN: ui_Screen6
void ui_Screen6_screen_init(void);
lv_obj_t *ui_Screen6;
lv_obj_t *ui_s6_Chart;
lv_obj_t *ui_s6_Header;
lv_obj_t *ui_s6_backLabel;
lv_obj_t *ui_s6_headerTitle;
lv_obj_t *ui_s6_headerTime;
void ui_event_s6_backButton( lv_event_t * e);
lv_obj_t *ui_s6_backButton;


// SCREEN: ui_Screen7
void ui_Screen7_screen_init(void);
lv_obj_t *ui_Screen7;
lv_obj_t *ui_s7_Header;
lv_obj_t *ui_s7_backLabel;
lv_obj_t *ui_s7_headerTitle;
lv_obj_t *ui_s7_headerTime;
void ui_event_s7_backButton( lv_event_t * e);
lv_obj_t *ui_s7_backButton;
lv_obj_t *ui_s7_panel1;
lv_obj_t *ui_s7_bar1;
lv_obj_t *ui_s7_value1;
lv_obj_t *ui_s7_name1;


// SCREEN: ui_Screen8
void ui_Screen8_screen_init(void);
lv_obj_t *ui_Screen8;
lv_obj_t *ui_s8_Header;
lv_obj_t *ui_s8_backLabel;
lv_obj_t *ui_s8_headerTitle;
lv_obj_t *ui_s8_headerTime;
void ui_event_s8_backButton( lv_event_t * e);
lv_obj_t *ui_s8_backButton;


// SCREEN: ui_Screen9
void ui_Screen9_screen_init(void);
lv_obj_t *ui_Screen9;
lv_obj_t *ui_s9_Header;
lv_obj_t *ui_s9_backLabel;
lv_obj_t *ui_s9_headerTitle;
lv_obj_t *ui_s9_headerTime;
void ui_event_s9_backButton( lv_event_t * e);
lv_obj_t *ui_s9_backButton;
lv_obj_t *ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_s0_Label01( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen1_screen_init);
}
}
void ui_event_s0_Label02( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen2_screen_init);
}
}
void ui_event_s0_Label03( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen3, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen3_screen_init);
}
}
void ui_event_s0_Label04( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen4, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen4_screen_init);
}
}
void ui_event_s0_Label05( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen5, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen5_screen_init);
}
}
void ui_event_s0_Label06( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen6, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen6_screen_init);
}
}
void ui_event_s0_Label08( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen8, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen8_screen_init);
}
}
void ui_event_s0_Label07( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen7, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen7_screen_init);
}
}
void ui_event_s0_Label09( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen9, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen9_screen_init);
}
}
void ui_event_s1_backButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_s1_tempSlider1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      _ui_slider_set_text_value( ui_s1_tempLabel1, target, "", "°");
}
}
void ui_event_s1_tempSlider2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      _ui_slider_set_text_value( ui_s1_tempLabel2, target, "", "°");
}
}
void ui_event_s1_tempSlider3( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      _ui_slider_set_text_value( ui_s1_tempLabel3, target, "", "°");
}
}
void ui_event_s2_backButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_s3_backButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_s4_backButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_s5_backButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_s6_backButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_s7_backButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_s8_backButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_s9_backButton( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}

///////////////////// SCREENS ////////////////////

void ui_init( void )
{
lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_Screen0_screen_init();
ui_Screen1_screen_init();
ui_Screen2_screen_init();
ui_Screen3_screen_init();
ui_Screen4_screen_init();
ui_Screen5_screen_init();
ui_Screen6_screen_init();
ui_Screen7_screen_init();
ui_Screen8_screen_init();
ui_Screen9_screen_init();
ui____initial_actions0 = lv_obj_create(NULL);
lv_disp_load_scr( ui_Screen0);
}