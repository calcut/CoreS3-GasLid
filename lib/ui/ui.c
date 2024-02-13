// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: CoreS3_SLS_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Screen0
void ui_Screen0_screen_init(void);
lv_obj_t *ui_Screen0;
void ui_event_Label01( lv_event_t * e);
lv_obj_t *ui_Label01;
void ui_event_Label02( lv_event_t * e);
lv_obj_t *ui_Label02;
void ui_event_Label03( lv_event_t * e);
lv_obj_t *ui_Label03;
void ui_event_Label4( lv_event_t * e);
lv_obj_t *ui_Label4;
void ui_event_Label05( lv_event_t * e);
lv_obj_t *ui_Label05;
void ui_event_Label06( lv_event_t * e);
lv_obj_t *ui_Label06;
void ui_event_Label08( lv_event_t * e);
lv_obj_t *ui_Label08;
void ui_event_Label07( lv_event_t * e);
lv_obj_t *ui_Label07;
void ui_event_Label09( lv_event_t * e);
lv_obj_t *ui_Label09;


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t *ui_Screen1;
lv_obj_t *ui_Header1;
lv_obj_t *ui_BackLabel01;
lv_obj_t *ui_Header_Title1;
void ui_event_Button1( lv_event_t * e);
lv_obj_t *ui_Button1;
void ui_event_Slider1_temp1( lv_event_t * e);
lv_obj_t *ui_Slider1_temp1;
lv_obj_t *ui_Label1_tank1;
lv_obj_t *ui_Label1_temp1;
lv_obj_t *ui_Label1_tank2;
void ui_event_Slider1_temp2( lv_event_t * e);
lv_obj_t *ui_Slider1_temp2;
lv_obj_t *ui_Label1_temp2;
void ui_event_Slider1_temp3( lv_event_t * e);
lv_obj_t *ui_Slider1_temp3;
lv_obj_t *ui_Label1_tank3;
lv_obj_t *ui_Label1_temp3;


// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
lv_obj_t *ui_Screen2;
lv_obj_t *ui_Header2;
lv_obj_t *ui_BackLabel02;
lv_obj_t *ui_Header_Title2;
void ui_event_Button2( lv_event_t * e);
lv_obj_t *ui_Button2;
lv_obj_t *ui_s2_label1;
lv_obj_t *ui_s2_Keyboard;
lv_obj_t *ui_s2_Switch1;
lv_obj_t *ui_s2_Time1;
lv_obj_t *ui_s2_Time2;
lv_obj_t *ui_s2_Time3;
lv_obj_t *ui_s2_Time4;
lv_obj_t *ui_s2_Switch3;
lv_obj_t *ui_Switch3;
lv_obj_t *ui_s2_Switch2;
lv_obj_t *ui_s2_Switch4;


// SCREEN: ui_Screen3
void ui_Screen3_screen_init(void);
lv_obj_t *ui_Screen3;
lv_obj_t *ui_Header3;
lv_obj_t *ui_BackLabel03;
lv_obj_t *ui_Header_Title3;
lv_obj_t *ui_Header_Time3;
lv_obj_t *ui_Bar1;
lv_obj_t *ui_Bar2;
lv_obj_t *ui_Bar3;
lv_obj_t *ui_Bar4;
lv_obj_t *ui_LabelRSSI;
lv_obj_t *ui_LabelConnected;
lv_obj_t *ui_LabelBand;
lv_obj_t *ui_LabelRat;
lv_obj_t *ui_LabelSerial;
lv_obj_t *ui_LabelSyncStatus;
lv_obj_t *ui_LabelDevice;
lv_obj_t *ui_LabelHubStatus;
lv_obj_t *ui_TextAreaHubStatus;
lv_obj_t *ui_TextAreaSyncStatus;
lv_obj_t *ui_Button3_Refresh;
lv_obj_t *ui_Label3_Refresh;
void ui_event_Button3( lv_event_t * e);
lv_obj_t *ui_Button3;


// SCREEN: ui_Screen4
void ui_Screen4_screen_init(void);
lv_obj_t *ui_Screen4;
lv_obj_t *ui_Image1;
lv_obj_t *ui_Header4;
lv_obj_t *ui_BackLabel04;
lv_obj_t *ui_Header_Title4;
lv_obj_t *ui_Label4_Ki_val;
lv_obj_t *ui_Label4_Kp_val;
lv_obj_t *ui_Label4_Kd_val;
lv_obj_t *ui_Label4_Setpoint_val;
lv_obj_t *ui_Label4_Error_val;
lv_obj_t *ui_Label4_Input_val;
lv_obj_t *ui_Label4_Iterm_val;
lv_obj_t *ui_Label4_Output_val;
lv_obj_t *ui_Label4_Pterm_val;
lv_obj_t *ui_Label4_Dterm_val;
void ui_event_Button4( lv_event_t * e);
lv_obj_t *ui_Button4;


// SCREEN: ui_Screen5
void ui_Screen5_screen_init(void);
lv_obj_t *ui_Screen5;
lv_obj_t *ui_Header5;
lv_obj_t *ui_BackLabel05;
lv_obj_t *ui_Header_Title5;
lv_obj_t *ui_TextAreaLog;
void ui_event_Button5( lv_event_t * e);
lv_obj_t *ui_Button5;


// SCREEN: ui_Screen6
void ui_Screen6_screen_init(void);
lv_obj_t *ui_Screen6;
lv_obj_t *ui_Chart1;
lv_obj_t *ui_Header6;
lv_obj_t *ui_BackLabel6;
lv_obj_t *ui_Header_Title6;
void ui_event_Button6( lv_event_t * e);
lv_obj_t *ui_Button6;


// SCREEN: ui_Screen7
void ui_Screen7_screen_init(void);
lv_obj_t *ui_Screen7;
lv_obj_t *ui_Header7;
lv_obj_t *ui_BackLabel7;
lv_obj_t *ui_Header_Title7;
void ui_event_Button7( lv_event_t * e);
lv_obj_t *ui_Button7;
lv_obj_t *ui_s7_panel1;
lv_obj_t *ui_s7_bar1;
lv_obj_t *ui_s7_value1;
lv_obj_t *ui_s7_name1;


// SCREEN: ui_Screen8
void ui_Screen8_screen_init(void);
lv_obj_t *ui_Screen8;
lv_obj_t *ui_Header8;
lv_obj_t *ui_BackLabel8;
lv_obj_t *ui_Header_Title8;
void ui_event_Button8( lv_event_t * e);
lv_obj_t *ui_Button8;


// SCREEN: ui_Screen9
void ui_Screen9_screen_init(void);
lv_obj_t *ui_Screen9;
lv_obj_t *ui_Header9;
lv_obj_t *ui_BackLabel9;
lv_obj_t *ui_Header_Title9;
void ui_event_Button9( lv_event_t * e);
lv_obj_t *ui_Button9;
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
void ui_event_Label01( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen1_screen_init);
}
}
void ui_event_Label02( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen2_screen_init);
}
}
void ui_event_Label03( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen3, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen3_screen_init);
}
}
void ui_event_Label4( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen4, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen4_screen_init);
}
}
void ui_event_Label05( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen5, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen5_screen_init);
}
}
void ui_event_Label06( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen6, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen6_screen_init);
}
}
void ui_event_Label08( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen8, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen8_screen_init);
}
}
void ui_event_Label07( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen7, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen7_screen_init);
}
}
void ui_event_Label09( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen9, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen9_screen_init);
}
}
void ui_event_Button1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_Slider1_temp1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      _ui_slider_set_text_value( ui_Label1_temp1, target, "", "°");
}
}
void ui_event_Slider1_temp2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      _ui_slider_set_text_value( ui_Label1_temp2, target, "", "°");
}
}
void ui_event_Slider1_temp3( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_VALUE_CHANGED) {
      _ui_slider_set_text_value( ui_Label1_temp3, target, "", "°");
}
}
void ui_event_Button2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_Button3( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_Button4( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_Button5( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_Button6( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_Button7( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_Button8( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);lv_obj_t * target = lv_event_get_target(e);
if ( event_code == LV_EVENT_CLICKED) {
      _ui_screen_change( &ui_Screen0, LV_SCR_LOAD_ANIM_FADE_ON, 150, 0, &ui_Screen0_screen_init);
}
}
void ui_event_Button9( lv_event_t * e) {
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
