#include "gui_helpers.h"

char text_buffer[64];

void setupGui(){

    lv_init();
    m5gfx_lvgl_init();
    ui_init();

    lv_timer_t * timer_datetime = lv_timer_create(display_date_time_labels, 1000, NULL);
    lv_timer_t * timer_notecard_info = lv_timer_create(display_notecard_info, 1000, NULL);
    lv_timer_t * timer_sensor_info = lv_timer_create(display_sensor_info, 1000, NULL);
    lv_timer_t * timer_pid_info = lv_timer_create(display_pid_info, 1000, NULL);
    lv_timer_t * timer_pressure_enthalpy = lv_timer_create(display_pressure_enthalpy, 1000, NULL);
    lv_timer_t * timer_log = lv_timer_create(display_log, 250, NULL);

    lv_obj_add_event_cb(ui_Screen3, nc_info_screen_event_cb, LV_EVENT_SCREEN_LOAD_START, NULL);
    lv_obj_add_event_cb(ui_Screen3, nc_info_screen_event_cb, LV_EVENT_SCREEN_UNLOAD_START, NULL);

    lv_obj_set_style_size(ui_Chart1, 0, LV_PART_INDICATOR);

    lv_chart_set_range( ui_Chart1, LV_CHART_AXIS_PRIMARY_X, 100, 800);
    lv_chart_set_range( ui_Chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 170);

    lv_chart_set_point_count(ui_Chart1, 10);
    lv_chart_series_t* ui_Chart1_series_1 = lv_chart_add_series(ui_Chart1, lv_color_hex(0x808080), LV_CHART_AXIS_PRIMARY_Y);
    static lv_coord_t ui_Chart1_r290_xarray[] = { 100, 175, 280, 400, 500, 600, 630, 600, 550, 525,};
    static lv_coord_t ui_Chart1_r290_yarray[] = {   0,  53, 103, 140, 160, 162, 141,  96,  36,   0,};
    lv_chart_set_ext_y_array(ui_Chart1, ui_Chart1_series_1, ui_Chart1_r290_yarray);
    lv_chart_set_ext_x_array(ui_Chart1, ui_Chart1_series_1, ui_Chart1_r290_xarray);
}

void nc_info_screen_event_cb(lv_event_t * event){
    if(event->code == LV_EVENT_SCREEN_LOAD_START){
        notecardManager.serviceEnabled = true;
    }
    else if(event->code == LV_EVENT_SCREEN_UNLOAD_START){
        notecardManager.serviceEnabled = false;
    }
}

void display_pressure_enthalpy(lv_timer_t * timer){

    // R290 Enthalpy Dome Data from
    // https://www.flycarpet.net/en/phonline
    // x	    y	    log(y) *100
    // 100	    1	      0
    // 175	    3.4	     53
    // 280	    10.7	103
    // 400	    25.4	140
    // 500	    40	    160
    // 600	    42	    162
    // 630	    25.8	141
    // 600	    9.2	     96
    // 550	    2.3	     36
    // 525	    1	      0
    if (lv_scr_act() == ui_Screen6){
        /*Do not display points on the data*/
        // lv_obj_set_style_size(ui_Chart1, 0, LV_PART_INDICATOR);

        // lv_chart_set_range( ui_Chart1, LV_CHART_AXIS_PRIMARY_X, 100, 800);
        // lv_chart_set_range( ui_Chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 170);

        // lv_chart_set_point_count(ui_Chart1, 10);
        // lv_chart_series_t* ui_Chart1_series_1 = lv_chart_add_series(ui_Chart1, lv_color_hex(0x808080), LV_CHART_AXIS_PRIMARY_Y);
        // static lv_coord_t ui_Chart1_r290_xarray[] = { 100, 175, 280, 400, 500, 600, 630, 600, 550, 525,};
        // static lv_coord_t ui_Chart1_r290_yarray[] = {   0,  53, 103, 140, 160, 162, 141,  96,  36,   0,};
        // lv_chart_set_ext_y_array(ui_Chart1, ui_Chart1_series_1, ui_Chart1_r290_yarray);
        // lv_chart_set_ext_x_array(ui_Chart1, ui_Chart1_series_1, ui_Chart1_r290_xarray);
    }
}

void display_pid_info(lv_timer_t * timer){
    if (lv_scr_act() == ui_Screen4){

        Serial.printf("PID info poll\n");

        sprintf(text_buffer, "%.3g", stateMachine.compressorPID->GetKp());
        lv_label_set_text(ui_Label4_Kp_val, text_buffer);

        sprintf(text_buffer, "%.3g", stateMachine.compressorPID->GetKi());
        lv_label_set_text(ui_Label4_Ki_val, text_buffer);

        sprintf(text_buffer, "%.3g", stateMachine.compressorPID->GetKd());
        lv_label_set_text(ui_Label4_Kd_val, text_buffer);

        sprintf(text_buffer, "%.3g", stateMachine.compressorPID->GetPterm());
        lv_label_set_text(ui_Label4_Pterm_val, text_buffer);

        //This is just the most recent term, not the integrated history
        // sprintf(text_buffer, "%.3g", compressorPID->GetIterm()); 

        sprintf(text_buffer, "%.3g", stateMachine.compressorPID->GetOutputSum()); //include history
        lv_label_set_text(ui_Label4_Iterm_val, text_buffer);

        sprintf(text_buffer, "%.3g", stateMachine.compressorPID->GetDterm());
        lv_label_set_text(ui_Label4_Dterm_val, text_buffer);

        sprintf(text_buffer, "%.3g", inputs.speedData["S1_Compressor"]);
        lv_label_set_text(ui_Label4_Output_val, text_buffer);

        sprintf(text_buffer, "%.3g", *stateMachine.compressorPIDsetpoint);
        lv_label_set_text(ui_Label4_Setpoint_val, text_buffer);

        sprintf(text_buffer, "%.3g", *stateMachine.compressorPIDinput);
        lv_label_set_text(ui_Label4_Input_val, text_buffer);

        sprintf(text_buffer, "%.3g", *stateMachine.compressorPIDsetpoint
                                     - *stateMachine.compressorPIDinput);
        lv_label_set_text(ui_Label4_Error_val, text_buffer);

    }
}


void display_notecard_info(lv_timer_t * timer){
    if (lv_scr_act() == ui_Screen3){    
        if(notecardManager.connected){
            lv_label_set_text(ui_LabelConnected, "Connected: Yes");
        }
        else{
            lv_label_set_text(ui_LabelConnected, "Connected: No");
        }

        sprintf(text_buffer, "UID: %s", notecardManager.deviceUID);
        lv_label_set_text(ui_LabelDevice, text_buffer);
        
        sprintf(text_buffer, "SN: %s", notecardManager.sn);
        lv_label_set_text(ui_LabelSerial, text_buffer);

        sprintf(text_buffer, "RSSI: %d dB", notecardManager.rssi);
        lv_label_set_text(ui_LabelRSSI, text_buffer);

        sprintf(text_buffer, "RAT: %s", notecardManager.rat);
        lv_label_set_text(ui_LabelRat, text_buffer);

        sprintf(text_buffer, "Band: %s", notecardManager.band);
        lv_label_set_text(ui_LabelBand, text_buffer);

        // fill in ui_BarX depending on reported bars
        if (notecardManager.bars > 0){
            lv_bar_set_value(ui_Bar1, 100, LV_ANIM_OFF);
        };
        if (notecardManager.bars > 1){
            lv_bar_set_value(ui_Bar2, 100, LV_ANIM_OFF);
        };
        if (notecardManager.bars > 2){
            lv_bar_set_value(ui_Bar3, 100, LV_ANIM_OFF);
        };
        if (notecardManager.bars > 3){
            lv_bar_set_value(ui_Bar4, 100, LV_ANIM_OFF);
        };

        lv_textarea_set_text(ui_TextAreaHubStatus, notecardManager.hub_status);
        lv_textarea_set_text(ui_TextAreaSyncStatus, notecardManager.hub_sync_status);

        if (notecardManager.serviceTick){
            lv_obj_clear_state(ui_Button3_Refresh, LV_STATE_CHECKED);
            lv_obj_add_state(ui_Button3_Refresh, LV_STATE_DISABLED);
        } else {
            lv_obj_clear_state(ui_Button3_Refresh, LV_STATE_DISABLED);
            lv_obj_add_state(ui_Button3_Refresh, LV_STATE_CHECKED);
        }
    }
}

void display_sensor_info(lv_timer_t * timer){
    if (lv_scr_act() == ui_Screen2){

        // gather the ui objects into arrays for easier looping
        lv_obj_t *tc_values[8] = {
            ui_Label2_value1,
            ui_Label2_value2,
            ui_Label2_value3,
            ui_Label2_value4,
            ui_Label2_value5,
            ui_Label2_value6
        };

        lv_obj_t *tc_names[8] = {
            ui_Label2_name1,
            ui_Label2_name2,
            ui_Label2_name3,
            ui_Label2_name4,
            ui_Label2_name5,
            ui_Label2_name6
        };

        lv_obj_t *pr_values[8] = {
            ui_Label2_value7,
            ui_Label2_value8
        };

        lv_obj_t *tc_bars[8] = {
            ui_Bar2_value1,
            ui_Bar2_value2,
            ui_Bar2_value3,
            ui_Bar2_value4,
            ui_Bar2_value5,
            ui_Bar2_value6
        };

        lv_obj_t *pr_bars[8] = {
            ui_Bar2_value7,
            ui_Bar2_value8
        };

        // loop over all ui_Label2_valueX objects and update with new values
        char* key;
        int i = 0;
        for (auto& keyval : inputs.temperatureData) {
            key = const_cast<char*>(keyval.first.c_str());
            sprintf(text_buffer, "%0.1f C", keyval.second);
            lv_label_set_text(tc_values[i], text_buffer);
            lv_label_set_text(tc_names[i], key);
            lv_bar_set_value(tc_bars[i], keyval.second, LV_ANIM_OFF);
            i++;
            if (i > 5) break;
        }

        // float value = inputs.temperatureData["Tr1_CompressorOut"];
        // sprintf(text_buffer, "%0.1f C", value);
        // lv_label_set_text(tc_values[0], text_buffer);
        // lv_bar_set_value(tc_bars[0], value, LV_ANIM_OFF);

        // for (int i = 0; i < 6; i++){
        //     sprintf(text_buffer, "%0.1f C", 99.9);
        //     lv_label_set_text(tc_values[i], text_buffer);
        //     lv_bar_set_value(tc_bars[i], 99.9, LV_ANIM_OFF);
        // }
    }
}

void display_date_time_labels(lv_timer_t * timer){
    //Get Time from system, then update the label on the display
    struct tm *time_info;
    struct timeval tv;
    char time_str[64];

    gettimeofday(&tv, NULL);
    time_info = localtime(&tv.tv_sec);

    // to show only the time
    strftime(time_str, sizeof(time_str), "%X", time_info);
    lv_label_set_text(ui_Header_Time1, time_str);
    lv_label_set_text(ui_Header_Time2, time_str);
    lv_label_set_text(ui_Header_Time3, time_str);
    lv_label_set_text(ui_Header_Time4, time_str);

    // silly hack to display boot time
    char * time_str_temp;
    time_str_temp = lv_label_get_text(ui_Header_Time5);
    if (strcmp("--:--:--", time_str_temp) == 0){
        lv_label_set_text(ui_Header_Time5, time_str);
    }
    // lv_label_set_text(ui_Header_Time5, time_str);

    // to show the full date and time
    // strftime(time_str, sizeof(time_str), "%Y-%m-%d %X", time_info);
    // lv_label_set_text(ui_Header_Time1, time_str);
    // lv_label_set_text(ui_Header_Time3, time_str);
}

void display_log(lv_timer_t * timer){
    lv_textarea_set_text(ui_TextAreaLog, serialDisplay.logBuffer);
}