#include "gui_populate_widgets.h"

lv_obj_t *ui_Panel2_sensor2;
lv_obj_t *ui_Bar2_value2;
lv_obj_t *ui_Label2_value2;
lv_obj_t *ui_Label2_name2;
lv_obj_t *ui_Panel2_sensor3;
lv_obj_t *ui_Bar2_value3;
lv_obj_t *ui_Label2_value3;
lv_obj_t *ui_Label2_name3;
lv_obj_t *ui_Panel2_sensor4;
lv_obj_t *ui_Bar2_value4;
lv_obj_t *ui_Label2_value4;
lv_obj_t *ui_Label2_name4;
lv_obj_t *ui_Panel2_sensor5;
lv_obj_t *ui_Bar2_value5;
lv_obj_t *ui_Label2_value5;
lv_obj_t *ui_Label2_name5;
lv_obj_t *ui_Panel2_sensor6;
lv_obj_t *ui_Bar2_value6;
lv_obj_t *ui_Label2_value6;
lv_obj_t *ui_Label2_name6;
lv_obj_t *ui_Panel2_sensor7;
lv_obj_t *ui_Bar2_value7;
lv_obj_t *ui_Label2_value7;
lv_obj_t *ui_Label2_name7;
lv_obj_t *ui_Panel2_sensor8;
lv_obj_t *ui_Bar2_value8;
lv_obj_t *ui_Label2_value8;
lv_obj_t *ui_Label2_name8;

void ui_Screen2_populate_widgets(){
    ui_Panel2_sensor2 = lv_obj_create(ui_Screen2);
    lv_obj_set_width( ui_Panel2_sensor2, 320);
    lv_obj_set_height( ui_Panel2_sensor2, 25);
    lv_obj_set_x( ui_Panel2_sensor2, 0 );
    lv_obj_set_y( ui_Panel2_sensor2, 50 );
    lv_obj_clear_flag( ui_Panel2_sensor2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_radius(ui_Panel2_sensor2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2_sensor2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_Panel2_sensor2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2_sensor2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    ui_Bar2_value2 = lv_bar_create(ui_Panel2_sensor2);
    lv_bar_set_range(ui_Bar2_value2, -10,50);
    lv_obj_set_width( ui_Bar2_value2, 95);
    lv_obj_set_height( ui_Bar2_value2, 10);
    lv_obj_set_x( ui_Bar2_value2, 60 );
    lv_obj_set_y( ui_Bar2_value2, -7 );

    ui_Label2_value2 = lv_label_create(ui_Panel2_sensor2);
    lv_obj_set_width( ui_Label2_value2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_value2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_value2, -2 );
    lv_obj_set_y( ui_Label2_value2, -10 );
    lv_label_set_text(ui_Label2_value2," 0.0 °C");

    ui_Label2_name2 = lv_label_create(ui_Panel2_sensor2);
    lv_obj_set_width( ui_Label2_name2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_name2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_name2, 165 );
    lv_obj_set_y( ui_Label2_name2, -10 );
    lv_label_set_text(ui_Label2_name2,"Compressor Out");

    ui_Panel2_sensor3 = lv_obj_create(ui_Screen2);
    lv_obj_set_width( ui_Panel2_sensor3, 320);
    lv_obj_set_height( ui_Panel2_sensor3, 25);
    lv_obj_set_x( ui_Panel2_sensor3, 0 );
    lv_obj_set_y( ui_Panel2_sensor3, 75 );
    lv_obj_clear_flag( ui_Panel2_sensor3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_radius(ui_Panel2_sensor3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2_sensor3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_Panel2_sensor3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2_sensor3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    ui_Bar2_value3 = lv_bar_create(ui_Panel2_sensor3);
    lv_bar_set_range(ui_Bar2_value3, -10,50);
    lv_obj_set_width( ui_Bar2_value3, 96);
    lv_obj_set_height( ui_Bar2_value3, 10);
    lv_obj_set_x( ui_Bar2_value3, 60 );
    lv_obj_set_y( ui_Bar2_value3, -7 );

    ui_Label2_value3 = lv_label_create(ui_Panel2_sensor3);
    lv_obj_set_width( ui_Label2_value3, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_value3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_value3, -2 );
    lv_obj_set_y( ui_Label2_value3, -10 );
    lv_label_set_text(ui_Label2_value3," 0.0 °C");

    ui_Label2_name3 = lv_label_create(ui_Panel2_sensor3);
    lv_obj_set_width( ui_Label2_name3, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_name3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_name3, 165 );
    lv_obj_set_y( ui_Label2_name3, -10 );
    lv_label_set_text(ui_Label2_name3,"Condenser Out");

    ui_Panel2_sensor4 = lv_obj_create(ui_Screen2);
    lv_obj_set_width( ui_Panel2_sensor4, 320);
    lv_obj_set_height( ui_Panel2_sensor4, 25);
    lv_obj_set_x( ui_Panel2_sensor4, 0 );
    lv_obj_set_y( ui_Panel2_sensor4, 100 );
    lv_obj_clear_flag( ui_Panel2_sensor4, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_radius(ui_Panel2_sensor4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2_sensor4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_Panel2_sensor4, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2_sensor4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    ui_Bar2_value4 = lv_bar_create(ui_Panel2_sensor4);
    lv_bar_set_range(ui_Bar2_value4, -10,50);
    lv_obj_set_width( ui_Bar2_value4, 95);
    lv_obj_set_height( ui_Bar2_value4, 10);
    lv_obj_set_x( ui_Bar2_value4, 60 );
    lv_obj_set_y( ui_Bar2_value4, -7 );

    ui_Label2_value4 = lv_label_create(ui_Panel2_sensor4);
    lv_obj_set_width( ui_Label2_value4, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_value4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_value4, -2 );
    lv_obj_set_y( ui_Label2_value4, -10 );
    lv_label_set_text(ui_Label2_value4," 0.0 °C");

    ui_Label2_name4 = lv_label_create(ui_Panel2_sensor4);
    lv_obj_set_width( ui_Label2_name4, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_name4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_name4, 165 );
    lv_obj_set_y( ui_Label2_name4, -10 );
    lv_label_set_text(ui_Label2_name4,"Flex Store Refr");

    ui_Panel2_sensor5 = lv_obj_create(ui_Screen2);
    lv_obj_set_width( ui_Panel2_sensor5, 320);
    lv_obj_set_height( ui_Panel2_sensor5, 25);
    lv_obj_set_x( ui_Panel2_sensor5, 0 );
    lv_obj_set_y( ui_Panel2_sensor5, 125 );
    lv_obj_clear_flag( ui_Panel2_sensor5, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_radius(ui_Panel2_sensor5, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2_sensor5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_Panel2_sensor5, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2_sensor5, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    ui_Bar2_value5 = lv_bar_create(ui_Panel2_sensor5);
    lv_bar_set_range(ui_Bar2_value5, -10,50);
    lv_obj_set_width( ui_Bar2_value5, 95);
    lv_obj_set_height( ui_Bar2_value5, 10);
    lv_obj_set_x( ui_Bar2_value5, 60 );
    lv_obj_set_y( ui_Bar2_value5, -7 );

    ui_Label2_value5 = lv_label_create(ui_Panel2_sensor5);
    lv_obj_set_width( ui_Label2_value5, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_value5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_value5, -2 );
    lv_obj_set_y( ui_Label2_value5, -10 );
    lv_label_set_text(ui_Label2_value5," 0.0 °C");

    ui_Label2_name5 = lv_label_create(ui_Panel2_sensor5);
    lv_obj_set_width( ui_Label2_name5, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_name5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_name5, 165 );
    lv_obj_set_y( ui_Label2_name5, -10 );
    lv_label_set_text(ui_Label2_name5,"Flex Store Water");

    ui_Panel2_sensor6 = lv_obj_create(ui_Screen2);
    lv_obj_set_width( ui_Panel2_sensor6, 320);
    lv_obj_set_height( ui_Panel2_sensor6, 25);
    lv_obj_set_x( ui_Panel2_sensor6, 0 );
    lv_obj_set_y( ui_Panel2_sensor6, 150 );
    lv_obj_clear_flag( ui_Panel2_sensor6, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_radius(ui_Panel2_sensor6, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2_sensor6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_Panel2_sensor6, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2_sensor6, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    ui_Bar2_value6 = lv_bar_create(ui_Panel2_sensor6);
    lv_bar_set_range(ui_Bar2_value6, -10,50);
    lv_obj_set_width( ui_Bar2_value6, 95);
    lv_obj_set_height( ui_Bar2_value6, 10);
    lv_obj_set_x( ui_Bar2_value6, 60 );
    lv_obj_set_y( ui_Bar2_value6, -7 );

    ui_Label2_value6 = lv_label_create(ui_Panel2_sensor6);
    lv_obj_set_width( ui_Label2_value6, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_value6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_value6, -2 );
    lv_obj_set_y( ui_Label2_value6, -10 );
    lv_label_set_text(ui_Label2_value6," 0.0 °C");

    ui_Label2_name6 = lv_label_create(ui_Panel2_sensor6);
    lv_obj_set_width( ui_Label2_name6, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_name6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_name6, 165 );
    lv_obj_set_y( ui_Label2_name6, -10 );
    lv_label_set_text(ui_Label2_name6,"Ambient (Air)");

    ui_Panel2_sensor7 = lv_obj_create(ui_Screen2);
    lv_obj_set_width( ui_Panel2_sensor7, 320);
    lv_obj_set_height( ui_Panel2_sensor7, 25);
    lv_obj_set_x( ui_Panel2_sensor7, 0 );
    lv_obj_set_y( ui_Panel2_sensor7, 175 );
    lv_obj_clear_flag( ui_Panel2_sensor7, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_radius(ui_Panel2_sensor7, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2_sensor7, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_Panel2_sensor7, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2_sensor7, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    ui_Bar2_value7 = lv_bar_create(ui_Panel2_sensor7);
    lv_bar_set_range(ui_Bar2_value7, -10,50);
    lv_obj_set_width( ui_Bar2_value7, 95);
    lv_obj_set_height( ui_Bar2_value7, 10);
    lv_obj_set_x( ui_Bar2_value7, 60 );
    lv_obj_set_y( ui_Bar2_value7, -7 );
    // lv_obj_set_style_bg_color(ui_Bar2_value7, lv_color_hex(0xDE9500), LV_PART_MAIN | LV_STATE_DEFAULT );
    // lv_obj_set_style_bg_opa(ui_Bar2_value7, 32, LV_PART_MAIN| LV_STATE_DEFAULT);

    // lv_obj_set_style_bg_color(ui_Bar2_value7, lv_color_hex(0xDE9500), LV_PART_INDICATOR | LV_STATE_DEFAULT );
    // lv_obj_set_style_bg_opa(ui_Bar2_value7, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

    ui_Label2_value7 = lv_label_create(ui_Panel2_sensor7);
    lv_obj_set_width( ui_Label2_value7, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_value7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_value7, -2 );
    lv_obj_set_y( ui_Label2_value7, -10 );
    lv_label_set_text(ui_Label2_value7," 0.0 Bar");

    ui_Label2_name7 = lv_label_create(ui_Panel2_sensor7);
    lv_obj_set_width( ui_Label2_name7, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_name7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_name7, 165 );
    lv_obj_set_y( ui_Label2_name7, -10 );
    lv_label_set_text(ui_Label2_name7,"Compressor Inlet");

    ui_Panel2_sensor8 = lv_obj_create(ui_Screen2);
    lv_obj_set_width( ui_Panel2_sensor8, 320);
    lv_obj_set_height( ui_Panel2_sensor8, 25);
    lv_obj_set_x( ui_Panel2_sensor8, 0 );
    lv_obj_set_y( ui_Panel2_sensor8, 200 );
    lv_obj_clear_flag( ui_Panel2_sensor8, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_radius(ui_Panel2_sensor8, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2_sensor8, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(ui_Panel2_sensor8, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2_sensor8, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    ui_Bar2_value8 = lv_bar_create(ui_Panel2_sensor8);
    lv_bar_set_range(ui_Bar2_value8, -10,50);
    lv_obj_set_width( ui_Bar2_value8, 95);
    lv_obj_set_height( ui_Bar2_value8, 10);
    lv_obj_set_x( ui_Bar2_value8, 60 );
    lv_obj_set_y( ui_Bar2_value8, -7 );
    // lv_obj_set_style_bg_color(ui_Bar2_value8, lv_color_hex(0xDE9500), LV_PART_MAIN | LV_STATE_DEFAULT );
    // lv_obj_set_style_bg_opa(ui_Bar2_value8, 32, LV_PART_MAIN| LV_STATE_DEFAULT);

    // lv_obj_set_style_bg_color(ui_Bar2_value8, lv_color_hex(0xDE9500), LV_PART_INDICATOR | LV_STATE_DEFAULT );
    // lv_obj_set_style_bg_opa(ui_Bar2_value8, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

    ui_Label2_value8 = lv_label_create(ui_Panel2_sensor8);
    lv_obj_set_width( ui_Label2_value8, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_value8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_value8, -2 );
    lv_obj_set_y( ui_Label2_value8, -10 );
    lv_label_set_text(ui_Label2_value8," 0.0 Bar");

    ui_Label2_name8 = lv_label_create(ui_Panel2_sensor8);
    lv_obj_set_width( ui_Label2_name8, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( ui_Label2_name8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( ui_Label2_name8, 165 );
    lv_obj_set_y( ui_Label2_name8, -10 );
    lv_label_set_text(ui_Label2_name8,"Compressor Out");
}