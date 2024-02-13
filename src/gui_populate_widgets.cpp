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

void ui_Screen2_build_row(lv_obj_t *panel, lv_obj_t *bar, lv_obj_t *labl_name, lv_obj_t *labl_value)
{

    static int index = 0;
    int delta_y = 25; //pixels

    lv_obj_set_width( panel, 320);
    lv_obj_set_height( panel, 25);
    lv_obj_set_x( panel, 0 );
    lv_obj_set_y( panel, 50 + (index * delta_y));
    lv_obj_clear_flag( panel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
    lv_obj_set_style_radius(panel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
    lv_obj_set_style_bg_opa(panel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(panel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

    lv_bar_set_range(bar, -10,50);
    lv_obj_set_width( bar, 95);
    lv_obj_set_height( bar, 10);
    lv_obj_set_x( bar, 60 );
    lv_obj_set_y( bar, -7 );

    lv_obj_set_width( labl_name, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height( labl_name, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( labl_name, 165 );
    lv_obj_set_y( labl_name, -10 );
    lv_label_set_text(labl_name,"Sensor Name");

    lv_obj_set_width( labl_value, 55);
    lv_obj_set_height( labl_value, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x( labl_value, -5 );
    lv_obj_set_y( labl_value, -10 );
    lv_label_set_long_mode(labl_value,LV_LABEL_LONG_DOT);
    lv_label_set_text(labl_value," --.-°C");
    lv_obj_set_style_text_align(labl_value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN| LV_STATE_DEFAULT);

    index++;
}

void ui_Screen2_populate_widgets(){

    ui_Panel2_sensor2 = lv_obj_create(ui_Screen2);
    ui_Bar2_value2 = lv_bar_create(ui_Panel2_sensor2);
    ui_Label2_value2 = lv_label_create(ui_Panel2_sensor2);
    ui_Label2_name2 = lv_label_create(ui_Panel2_sensor2);

    ui_Panel2_sensor3 = lv_obj_create(ui_Screen2);
    ui_Bar2_value3 = lv_bar_create(ui_Panel2_sensor3);
    ui_Label2_value3 = lv_label_create(ui_Panel2_sensor3);
    ui_Label2_name3 = lv_label_create(ui_Panel2_sensor3);

    ui_Panel2_sensor4 = lv_obj_create(ui_Screen2);
    ui_Bar2_value4 = lv_bar_create(ui_Panel2_sensor4);
    ui_Label2_value4 = lv_label_create(ui_Panel2_sensor4);
    ui_Label2_name4 = lv_label_create(ui_Panel2_sensor4);

    ui_Panel2_sensor5 = lv_obj_create(ui_Screen2);
    ui_Bar2_value5 = lv_bar_create(ui_Panel2_sensor5);
    ui_Label2_value5 = lv_label_create(ui_Panel2_sensor5);
    ui_Label2_name5 = lv_label_create(ui_Panel2_sensor5);

    ui_Panel2_sensor6 = lv_obj_create(ui_Screen2);
    ui_Bar2_value6 = lv_bar_create(ui_Panel2_sensor6);
    ui_Label2_value6 = lv_label_create(ui_Panel2_sensor6);
    ui_Label2_name6 = lv_label_create(ui_Panel2_sensor6);

    ui_Panel2_sensor7 = lv_obj_create(ui_Screen2);
    ui_Bar2_value7 = lv_bar_create(ui_Panel2_sensor7);
    ui_Label2_value7 = lv_label_create(ui_Panel2_sensor7);
    ui_Label2_name7 = lv_label_create(ui_Panel2_sensor7);

    ui_Panel2_sensor8 = lv_obj_create(ui_Screen2);
    ui_Bar2_value8 = lv_bar_create(ui_Panel2_sensor8);
    ui_Label2_value8 = lv_label_create(ui_Panel2_sensor8);
    ui_Label2_name8 = lv_label_create(ui_Panel2_sensor8);


    ui_Screen2_build_row(
        ui_Panel2_sensor2, 
        ui_Bar2_value2, 
        ui_Label2_name2, 
        ui_Label2_value2
    );

    ui_Screen2_build_row(
        ui_Panel2_sensor3, 
        ui_Bar2_value3, 
        ui_Label2_name3, 
        ui_Label2_value3
    );

    ui_Screen2_build_row(
        ui_Panel2_sensor4, 
        ui_Bar2_value4, 
        ui_Label2_name4, 
        ui_Label2_value4
    );

    ui_Screen2_build_row(
        ui_Panel2_sensor5, 
        ui_Bar2_value5, 
        ui_Label2_name5, 
        ui_Label2_value5
    );

    ui_Screen2_build_row(
        ui_Panel2_sensor6, 
        ui_Bar2_value6, 
        ui_Label2_name6, 
        ui_Label2_value6
    );

    ui_Screen2_build_row(
        ui_Panel2_sensor7, 
        ui_Bar2_value7, 
        ui_Label2_name7, 
        ui_Label2_value7
    );

    ui_Screen2_build_row(
        ui_Panel2_sensor8, 
        ui_Bar2_value8, 
        ui_Label2_name8, 
        ui_Label2_value8
    );
}

    