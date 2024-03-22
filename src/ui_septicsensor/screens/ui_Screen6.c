// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: SepticSensor_SLS_Project

#include "../ui.h"

void ui_Screen6_screen_init(void)
{
ui_Screen6 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen6, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_s6_Chart = lv_chart_create(ui_Screen6);
lv_obj_set_width( ui_s6_Chart, 309);
lv_obj_set_height( ui_s6_Chart, 204);
lv_obj_set_x( ui_s6_Chart, 5 );
lv_obj_set_y( ui_s6_Chart, 31 );
lv_chart_set_type( ui_s6_Chart, LV_CHART_TYPE_SCATTER);
lv_chart_set_range( ui_s6_Chart, LV_CHART_AXIS_PRIMARY_Y, 0, 150);
lv_chart_set_div_line_count( ui_s6_Chart, 0, 0);
lv_chart_set_axis_tick( ui_s6_Chart, LV_CHART_AXIS_PRIMARY_X, 0, 0, 5, 2, false, 50);
lv_chart_set_axis_tick( ui_s6_Chart, LV_CHART_AXIS_PRIMARY_Y, 0, 0, 0, 0, false, 50);
lv_chart_set_axis_tick( ui_s6_Chart, LV_CHART_AXIS_SECONDARY_Y, 0, 0, 5, 2, false, 25);



ui_s6_Header = lv_obj_create(ui_Screen6);
lv_obj_set_height( ui_s6_Header, 25);
lv_obj_set_width( ui_s6_Header, lv_pct(100));
lv_obj_set_align( ui_s6_Header, LV_ALIGN_TOP_MID );
lv_obj_clear_flag( ui_s6_Header, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_s6_Header, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_s6_Header, lv_color_hex(0x14191E), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_s6_Header, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_s6_Header, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_s6_backLabel = lv_label_create(ui_s6_Header);
lv_obj_set_width( ui_s6_backLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_s6_backLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_s6_backLabel, 0 );
lv_obj_set_y( ui_s6_backLabel, -20 );
lv_label_set_text(ui_s6_backLabel,"<");
lv_obj_set_style_text_color(ui_s6_backLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_s6_backLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_s6_backLabel, &lv_font_montserrat_34, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_s6_headerTitle = lv_label_create(ui_s6_Header);
lv_obj_set_width( ui_s6_headerTitle, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_s6_headerTitle, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_s6_headerTitle, 0 );
lv_obj_set_y( ui_s6_headerTitle, -9 );
lv_obj_set_align( ui_s6_headerTitle, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_s6_headerTitle,"Screen 6");
lv_obj_set_style_text_color(ui_s6_headerTitle, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_s6_headerTitle, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_s6_headerTime = lv_label_create(ui_s6_Header);
lv_obj_set_width( ui_s6_headerTime, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_s6_headerTime, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_s6_headerTime, LV_ALIGN_RIGHT_MID );
lv_label_set_text(ui_s6_headerTime,"--:--:--");
lv_obj_set_style_text_color(ui_s6_headerTime, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_s6_headerTime, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_s6_backButton = lv_btn_create(ui_Screen6);
lv_obj_set_width( ui_s6_backButton, 100);
lv_obj_set_height( ui_s6_backButton, 80);
lv_obj_add_flag( ui_s6_backButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_s6_backButton, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_s6_backButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_s6_backButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_s6_backButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_s6_backButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(ui_s6_backButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_shadow_opa(ui_s6_backButton, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_s6_backButton, ui_event_s6_backButton, LV_EVENT_ALL, NULL);

}
