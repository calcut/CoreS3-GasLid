#include "gui_populate_widgets.h"

lv_obj_t *ui_s7_panel1;
lv_obj_t *ui_s7_bar1;
lv_obj_t *ui_s7_value1;
lv_obj_t *ui_s7_name1;
lv_obj_t *ui_s7_panel2;
lv_obj_t *ui_s7_bar2;
lv_obj_t *ui_s7_value2;
lv_obj_t *ui_s7_name2;
lv_obj_t *ui_s7_panel3;
lv_obj_t *ui_s7_bar3;
lv_obj_t *ui_s7_value3;
lv_obj_t *ui_s7_name3;
lv_obj_t *ui_s7_panel4;
lv_obj_t *ui_s7_bar4;
lv_obj_t *ui_s7_value4;
lv_obj_t *ui_s7_name4;
lv_obj_t *ui_s7_panel5;
lv_obj_t *ui_s7_bar5;
lv_obj_t *ui_s7_value5;
lv_obj_t *ui_s7_name5;
lv_obj_t *ui_s7_panel6;
lv_obj_t *ui_s7_bar6;
lv_obj_t *ui_s7_value6;
lv_obj_t *ui_s7_name6;
lv_obj_t *ui_s7_panel7;
lv_obj_t *ui_s7_bar7;
lv_obj_t *ui_s7_value7;
lv_obj_t *ui_s7_name7;
lv_obj_t *ui_s7_panel8;
lv_obj_t *ui_s7_bar8;
lv_obj_t *ui_s7_value8;
lv_obj_t *ui_s7_name8;

lv_obj_t *ui_s8_panel1;
lv_obj_t *ui_s8_bar1;
lv_obj_t *ui_s8_value1;
lv_obj_t *ui_s8_name1;
lv_obj_t *ui_s8_panel2;
lv_obj_t *ui_s8_bar2;
lv_obj_t *ui_s8_value2;
lv_obj_t *ui_s8_name2;
lv_obj_t *ui_s8_panel3;
lv_obj_t *ui_s8_bar3;
lv_obj_t *ui_s8_value3;
lv_obj_t *ui_s8_name3;
lv_obj_t *ui_s8_panel4;
lv_obj_t *ui_s8_bar4;
lv_obj_t *ui_s8_value4;
lv_obj_t *ui_s8_name4;
lv_obj_t *ui_s8_panel5;
lv_obj_t *ui_s8_bar5;
lv_obj_t *ui_s8_value5;
lv_obj_t *ui_s8_name5;
lv_obj_t *ui_s8_panel6;
lv_obj_t *ui_s8_bar6;
lv_obj_t *ui_s8_value6;
lv_obj_t *ui_s8_name6;
lv_obj_t *ui_s8_panel7;
lv_obj_t *ui_s8_bar7;
lv_obj_t *ui_s8_value7;
lv_obj_t *ui_s8_name7;
lv_obj_t *ui_s8_panel8;
lv_obj_t *ui_s8_bar8;
lv_obj_t *ui_s8_value8;
lv_obj_t *ui_s8_name8;

lv_obj_t *ui_s9_panel1;
lv_obj_t *ui_s9_bar1;
lv_obj_t *ui_s9_value1;
lv_obj_t *ui_s9_name1;
lv_obj_t *ui_s9_panel2;
lv_obj_t *ui_s9_bar2;
lv_obj_t *ui_s9_value2;
lv_obj_t *ui_s9_name2;
lv_obj_t *ui_s9_panel3;
lv_obj_t *ui_s9_bar3;
lv_obj_t *ui_s9_value3;
lv_obj_t *ui_s9_name3;
lv_obj_t *ui_s9_panel4;
lv_obj_t *ui_s9_bar4;
lv_obj_t *ui_s9_value4;
lv_obj_t *ui_s9_name4;
lv_obj_t *ui_s9_panel5;
lv_obj_t *ui_s9_bar5;
lv_obj_t *ui_s9_value5;
lv_obj_t *ui_s9_name5;
lv_obj_t *ui_s9_panel6;
lv_obj_t *ui_s9_bar6;
lv_obj_t *ui_s9_value6;
lv_obj_t *ui_s9_name6;
lv_obj_t *ui_s9_panel7;
lv_obj_t *ui_s9_bar7;
lv_obj_t *ui_s9_value7;
lv_obj_t *ui_s9_name7;
lv_obj_t *ui_s9_panel8;
lv_obj_t *ui_s9_bar8;
lv_obj_t *ui_s9_value8;
lv_obj_t *ui_s9_name8;


void build_row(lv_obj_t *panel, lv_obj_t *bar, lv_obj_t *labl_name, lv_obj_t *labl_value)
{

    static int index = 1;
    int delta_y = 25; //pixels

    lv_obj_set_width( panel, 320);
    lv_obj_set_height( panel, 25);
    lv_obj_set_x( panel, 0 );
    lv_obj_set_y( panel, 25 + (index * delta_y));
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
    if (index > 7) index = 0;
}

void populate_widgets(){

    ui_s7_panel2= lv_obj_create(ui_Screen7);
    ui_s7_bar2 = lv_bar_create(ui_s7_panel2);
    ui_s7_value2 = lv_label_create(ui_s7_panel2);
    ui_s7_name2 = lv_label_create(ui_s7_panel2);

    ui_s7_panel3= lv_obj_create(ui_Screen7);
    ui_s7_bar3 = lv_bar_create(ui_s7_panel3);
    ui_s7_value3 = lv_label_create(ui_s7_panel3);
    ui_s7_name3 = lv_label_create(ui_s7_panel3);

    ui_s7_panel4= lv_obj_create(ui_Screen7);
    ui_s7_bar4 = lv_bar_create(ui_s7_panel4);
    ui_s7_value4 = lv_label_create(ui_s7_panel4);
    ui_s7_name4 = lv_label_create(ui_s7_panel4);

    ui_s7_panel5= lv_obj_create(ui_Screen7);
    ui_s7_bar5 = lv_bar_create(ui_s7_panel5);
    ui_s7_value5 = lv_label_create(ui_s7_panel5);
    ui_s7_name5 = lv_label_create(ui_s7_panel5);

    ui_s7_panel6= lv_obj_create(ui_Screen7);
    ui_s7_bar6 = lv_bar_create(ui_s7_panel6);
    ui_s7_value6 = lv_label_create(ui_s7_panel6);
    ui_s7_name6 = lv_label_create(ui_s7_panel6);

    ui_s7_panel7= lv_obj_create(ui_Screen7);
    ui_s7_bar7 = lv_bar_create(ui_s7_panel7);
    ui_s7_value7 = lv_label_create(ui_s7_panel7);
    ui_s7_name7 = lv_label_create(ui_s7_panel7);

    ui_s7_panel8= lv_obj_create(ui_Screen7);
    ui_s7_bar8 = lv_bar_create(ui_s7_panel8);
    ui_s7_value8 = lv_label_create(ui_s7_panel8);
    ui_s7_name8 = lv_label_create(ui_s7_panel8);

    // build_row(
    //     ui_s7_panel1, 
    //     ui_s7_bar1, 
    //     ui_s7_name1, 
    //     ui_s7_value1
    // );

    build_row(
        ui_s7_panel2, 
        ui_s7_bar2, 
        ui_s7_name2, 
        ui_s7_value2
    );

    build_row(
        ui_s7_panel3, 
        ui_s7_bar3, 
        ui_s7_name3, 
        ui_s7_value3
    );

    build_row(
        ui_s7_panel4, 
        ui_s7_bar4, 
        ui_s7_name4, 
        ui_s7_value4
    );

    build_row(
        ui_s7_panel5, 
        ui_s7_bar5, 
        ui_s7_name5, 
        ui_s7_value5
    );

    build_row(
        ui_s7_panel6, 
        ui_s7_bar6, 
        ui_s7_name6, 
        ui_s7_value6
    );

    build_row(
        ui_s7_panel7, 
        ui_s7_bar7, 
        ui_s7_name7, 
        ui_s7_value7
    );

    build_row(
        ui_s7_panel8, 
        ui_s7_bar8, 
        ui_s7_name8, 
        ui_s7_value8
    );

    ui_s8_panel1= lv_obj_create(ui_Screen8);
    ui_s8_bar1 = lv_bar_create(ui_s8_panel1);
    ui_s8_value1 = lv_label_create(ui_s8_panel1);
    ui_s8_name1 = lv_label_create(ui_s8_panel1);

    ui_s8_panel2= lv_obj_create(ui_Screen8);
    ui_s8_bar2 = lv_bar_create(ui_s8_panel2);
    ui_s8_value2 = lv_label_create(ui_s8_panel2);
    ui_s8_name2 = lv_label_create(ui_s8_panel2);

    ui_s8_panel3= lv_obj_create(ui_Screen8);
    ui_s8_bar3 = lv_bar_create(ui_s8_panel3);
    ui_s8_value3 = lv_label_create(ui_s8_panel3);
    ui_s8_name3 = lv_label_create(ui_s8_panel3);

    ui_s8_panel4= lv_obj_create(ui_Screen8);
    ui_s8_bar4 = lv_bar_create(ui_s8_panel4);
    ui_s8_value4 = lv_label_create(ui_s8_panel4);
    ui_s8_name4 = lv_label_create(ui_s8_panel4);

    ui_s8_panel5= lv_obj_create(ui_Screen8);
    ui_s8_bar5 = lv_bar_create(ui_s8_panel5);
    ui_s8_value5 = lv_label_create(ui_s8_panel5);
    ui_s8_name5 = lv_label_create(ui_s8_panel5);

    ui_s8_panel6= lv_obj_create(ui_Screen8);
    ui_s8_bar6 = lv_bar_create(ui_s8_panel6);
    ui_s8_value6 = lv_label_create(ui_s8_panel6);
    ui_s8_name6 = lv_label_create(ui_s8_panel6);

    ui_s8_panel7= lv_obj_create(ui_Screen8);
    ui_s8_bar7 = lv_bar_create(ui_s8_panel7);
    ui_s8_value7 = lv_label_create(ui_s8_panel7);
    ui_s8_name7 = lv_label_create(ui_s8_panel7);

    ui_s8_panel8= lv_obj_create(ui_Screen8);
    ui_s8_bar8 = lv_bar_create(ui_s8_panel8);
    ui_s8_value8 = lv_label_create(ui_s8_panel8);
    ui_s8_name8 = lv_label_create(ui_s8_panel8);

    build_row(
        ui_s8_panel1, 
        ui_s8_bar1, 
        ui_s8_name1, 
        ui_s8_value1
    );

    build_row(
        ui_s8_panel2, 
        ui_s8_bar2, 
        ui_s8_name2, 
        ui_s8_value2
    );

    build_row(
        ui_s8_panel3, 
        ui_s8_bar3, 
        ui_s8_name3, 
        ui_s8_value3
    );

    build_row(
        ui_s8_panel4, 
        ui_s8_bar4, 
        ui_s8_name4, 
        ui_s8_value4
    );

    build_row(
        ui_s8_panel5, 
        ui_s8_bar5, 
        ui_s8_name5, 
        ui_s8_value5
    );

    build_row(
        ui_s8_panel6, 
        ui_s8_bar6, 
        ui_s8_name6, 
        ui_s8_value6
    );

    build_row(
        ui_s8_panel7, 
        ui_s8_bar7, 
        ui_s8_name7, 
        ui_s8_value7
    );

    build_row(
        ui_s8_panel8, 
        ui_s8_bar8, 
        ui_s8_name8, 
        ui_s8_value8
    );

    ui_s9_panel1= lv_obj_create(ui_Screen9);
    ui_s9_bar1 = lv_bar_create(ui_s9_panel1);
    ui_s9_value1 = lv_label_create(ui_s9_panel1);
    ui_s9_name1 = lv_label_create(ui_s9_panel1);

    ui_s9_panel2= lv_obj_create(ui_Screen9);
    ui_s9_bar2 = lv_bar_create(ui_s9_panel2);
    ui_s9_value2 = lv_label_create(ui_s9_panel2);
    ui_s9_name2 = lv_label_create(ui_s9_panel2);

    ui_s9_panel3= lv_obj_create(ui_Screen9);
    ui_s9_bar3 = lv_bar_create(ui_s9_panel3);
    ui_s9_value3 = lv_label_create(ui_s9_panel3);
    ui_s9_name3 = lv_label_create(ui_s9_panel3);

    ui_s9_panel4= lv_obj_create(ui_Screen9);
    ui_s9_bar4 = lv_bar_create(ui_s9_panel4);
    ui_s9_value4 = lv_label_create(ui_s9_panel4);
    ui_s9_name4 = lv_label_create(ui_s9_panel4);

    ui_s9_panel5= lv_obj_create(ui_Screen9);
    ui_s9_bar5 = lv_bar_create(ui_s9_panel5);
    ui_s9_value5 = lv_label_create(ui_s9_panel5);
    ui_s9_name5 = lv_label_create(ui_s9_panel5);

    ui_s9_panel6= lv_obj_create(ui_Screen9);
    ui_s9_bar6 = lv_bar_create(ui_s9_panel6);
    ui_s9_value6 = lv_label_create(ui_s9_panel6);
    ui_s9_name6 = lv_label_create(ui_s9_panel6);

    ui_s9_panel7= lv_obj_create(ui_Screen9);
    ui_s9_bar7 = lv_bar_create(ui_s9_panel7);
    ui_s9_value7 = lv_label_create(ui_s9_panel7);
    ui_s9_name7 = lv_label_create(ui_s9_panel7);

    ui_s9_panel8= lv_obj_create(ui_Screen9);
    ui_s9_bar8 = lv_bar_create(ui_s9_panel8);
    ui_s9_value8 = lv_label_create(ui_s9_panel8);
    ui_s9_name8 = lv_label_create(ui_s9_panel8);

    build_row(
        ui_s9_panel1, 
        ui_s9_bar1, 
        ui_s9_name1, 
        ui_s9_value1
    );

    build_row(
        ui_s9_panel2, 
        ui_s9_bar2, 
        ui_s9_name2, 
        ui_s9_value2
    );

    build_row(
        ui_s9_panel3, 
        ui_s9_bar3, 
        ui_s9_name3, 
        ui_s9_value3
    );

    build_row(
        ui_s9_panel4, 
        ui_s9_bar4, 
        ui_s9_name4, 
        ui_s9_value4
    );

    build_row(
        ui_s9_panel5, 
        ui_s9_bar5, 
        ui_s9_name5, 
        ui_s9_value5
    );

    build_row(
        ui_s9_panel6, 
        ui_s9_bar6, 
        ui_s9_name6, 
        ui_s9_value6
    );

    build_row(
        ui_s9_panel7, 
        ui_s9_bar7, 
        ui_s9_name7, 
        ui_s9_value7
    );

    build_row(
        ui_s9_panel8, 
        ui_s9_bar8, 
        ui_s9_name8, 
        ui_s9_value8
    );

    //Keep back buttons on top so they can be pressed
    lv_obj_move_foreground(ui_s7_backButton);
    lv_obj_move_foreground(ui_s8_backButton);
    lv_obj_move_foreground(ui_s9_backButton);
}
