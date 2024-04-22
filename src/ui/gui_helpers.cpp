#include "gui_helpers.h"

char text_buffer[64];

static void gas_sample_time_text_event_cb(lv_event_t * e);
static void gas_sample_selected_event_cb(lv_event_t * e);
static void gas_sample_go_event_cb(lv_event_t * e);
static void gas_sample_stop_event_cb(lv_event_t * e);


void setupGui(){

    initDisplay();
    ui_init();

    lv_timer_t * timer_datetime = lv_timer_create(display_date_time_labels, 1000, NULL);
    lv_timer_t * timer_notecard_info = lv_timer_create(display_notecard_info, 1000, NULL);
    lv_timer_t * timer_sensor_info = lv_timer_create(display_sensor_info, 1000, NULL);
    lv_timer_t * timer_pid_info = lv_timer_create(display_pid_info, 1000, NULL);
    lv_timer_t * timer_log = lv_timer_create(display_log, 250, NULL);

    lv_obj_add_event_cb(ui_Screen3, nc_info_screen_event_cb, LV_EVENT_SCREEN_LOAD_START, NULL);
    lv_obj_add_event_cb(ui_Screen3, nc_info_screen_event_cb, LV_EVENT_SCREEN_UNLOAD_START, NULL);

    lv_obj_add_event_cb(ui_s1_tempSlider1, jacketslider_cb, LV_EVENT_RELEASED, NULL);
    lv_obj_add_event_cb(ui_s1_tempSlider2, jacketslider_cb, LV_EVENT_RELEASED, NULL);
    lv_obj_add_event_cb(ui_s1_tempSlider3, jacketslider_cb, LV_EVENT_RELEASED, NULL);

    lv_obj_add_event_cb(ui_s2_GoButton, gas_sample_go_event_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(ui_s2_StopButton, gas_sample_stop_event_cb, LV_EVENT_PRESSED, NULL);

    populate_widgets();
    display_refresh_envVars();

}

void nc_info_screen_event_cb(lv_event_t * event){
    if(event->code == LV_EVENT_SCREEN_LOAD_START){
        notecardManager.serviceEnabled = true;
    }
    else if(event->code == LV_EVENT_SCREEN_UNLOAD_START){
        notecardManager.serviceEnabled = false;
    }
}

void jacketslider_cb(lv_event_t * e)
{
    lv_obj_t * target = lv_event_get_target(e);
    char temp[4];
    sprintf(temp, "%d", (int)lv_slider_get_value(target));
	// ESP_LOGI("GUI", "Slider1 event %s", temp);
    // stateMachine.envVars["targetTempTank1"] = temp;
    // changeEnvVar("targetTempTank1", temp);
    // notecardManager.getEnvironment();

    if (target == ui_s1_tempSlider1){
            changeEnvVar("targetTempTank1", temp);
    }
    else if (target == ui_s1_tempSlider2){
            changeEnvVar("targetTempTank2", temp);
    }
    else if (target == ui_s1_tempSlider3){
            changeEnvVar("targetTempTank3", temp);
    }
}

void display_refresh_envVars(){
    //to be called when environment variables have been updated

    //Screen1
    sprintf(text_buffer, "%d°", (int)stateMachine.envVars["targetTempTank1"]);
    lv_label_set_text(ui_s1_tempLabel1, text_buffer);
    lv_slider_set_value(ui_s1_tempSlider1, (int)stateMachine.envVars["targetTempTank1"], LV_ANIM_OFF);

    sprintf(text_buffer, "%d°", (int)stateMachine.envVars["targetTempTank2"]);
    lv_label_set_text(ui_s1_tempLabel2, text_buffer);
    lv_slider_set_value(ui_s1_tempSlider2, (int)stateMachine.envVars["targetTempTank2"], LV_ANIM_OFF);

    sprintf(text_buffer, "%d°", (int)stateMachine.envVars["targetTempTank3"]);
    lv_label_set_text(ui_s1_tempLabel3, text_buffer);
    lv_slider_set_value(ui_s1_tempSlider3, (int)stateMachine.envVars["targetTempTank3"], LV_ANIM_OFF);

    //Screen2
    char buf[6];
    //need to remove the callbacks to avoid infinite loop
    lv_obj_remove_event_cb(ui_s2_Time1, gas_sample_time_text_event_cb); 
    lv_obj_remove_event_cb(ui_s2_Time2, gas_sample_time_text_event_cb);
    lv_obj_remove_event_cb(ui_s2_Time3, gas_sample_time_text_event_cb);
    lv_obj_remove_event_cb(ui_s2_Time4, gas_sample_time_text_event_cb);

    sprintf(buf, "%02d:%02d", (int)stateMachine.envVars["sampleTime1_hour"], (int)stateMachine.envVars["sampleTime1_min"]);
    lv_textarea_set_text(ui_s2_Time1, buf);
    sprintf(buf, "%02d:%02d", (int)stateMachine.envVars["sampleTime2_hour"], (int)stateMachine.envVars["sampleTime2_min"]);
    lv_textarea_set_text(ui_s2_Time2, buf);
    sprintf(buf, "%02d:%02d", (int)stateMachine.envVars["sampleTime3_hour"], (int)stateMachine.envVars["sampleTime3_min"]);
    lv_textarea_set_text(ui_s2_Time3, buf);
    sprintf(buf, "%02d:%02d", (int)stateMachine.envVars["sampleTime4_hour"], (int)stateMachine.envVars["sampleTime4_min"]);
    lv_textarea_set_text(ui_s2_Time4, buf);

    //add the callbacks back
    lv_obj_add_event_cb(ui_s2_Time1, gas_sample_time_text_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_s2_Time2, gas_sample_time_text_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_s2_Time3, gas_sample_time_text_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_s2_Time4, gas_sample_time_text_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ui_s2_Time1, gas_sample_selected_event_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(ui_s2_Time2, gas_sample_selected_event_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(ui_s2_Time3, gas_sample_selected_event_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(ui_s2_Time4, gas_sample_selected_event_cb, LV_EVENT_PRESSED, NULL);
    
}

void display_pid_info(lv_timer_t * timer){
    if (lv_scr_act() == ui_Screen4){

        sprintf(text_buffer, "%.3g", stateMachine.gasPID->GetKp());
        lv_label_set_text(ui_s4_Kp_val, text_buffer);

        sprintf(text_buffer, "%.3g", stateMachine.gasPID->GetKi());
        lv_label_set_text(ui_s4_Ki_val, text_buffer);

        sprintf(text_buffer, "%.3g", stateMachine.gasPID->GetKd());
        lv_label_set_text(ui_s4_Kd_val, text_buffer);

        sprintf(text_buffer, "%.3g", stateMachine.gasPID->GetPterm());
        lv_label_set_text(ui_s4_Pterm_val, text_buffer);

        //This is just the most recent term, not the integrated history
        // sprintf(text_buffer, "%.3g", gasPID->GetIterm()); 

        sprintf(text_buffer, "%.3g", stateMachine.gasPID->GetOutputSum()); //include history
        lv_label_set_text(ui_s4_Iterm_val, text_buffer);

        sprintf(text_buffer, "%.3g", stateMachine.gasPID->GetDterm());
        lv_label_set_text(ui_s4_Dterm_val, text_buffer);

        sprintf(text_buffer, "%.3g", stateMachine.gasPIDoutput);
        lv_label_set_text(ui_s4_Output_val, text_buffer);

        sprintf(text_buffer, "%.3g", *stateMachine.gasPIDsetpoint);
        lv_label_set_text(ui_s4_Setpoint_val, text_buffer);

        sprintf(text_buffer, "%.3g", *stateMachine.gasPIDinput);
        lv_label_set_text(ui_s4_Input_val, text_buffer);

        sprintf(text_buffer, "%.3g", *stateMachine.gasPIDsetpoint
                                     - *stateMachine.gasPIDinput);
        lv_label_set_text(ui_s4_Error_val, text_buffer);

    }
}


void display_notecard_info(lv_timer_t * timer){
    if (lv_scr_act() == ui_Screen3){    
        if(notecardManager.connected){
            lv_label_set_text(ui_s3_LabelConnected, "Connected: Yes");
        }
        else{
            lv_label_set_text(ui_s3_LabelConnected, "Connected: No");
        }

        sprintf(text_buffer, "UID: %s", notecardManager.deviceUID);
        lv_label_set_text(ui_s3_LabelDevice, text_buffer);
        
        sprintf(text_buffer, "SN: %s", notecardManager.sn);
        lv_label_set_text(ui_s3_LabelSerial, text_buffer);

        sprintf(text_buffer, "RSSI: %d dB", notecardManager.rssi);
        lv_label_set_text(ui_s3_LabelRSSI, text_buffer);

        sprintf(text_buffer, "RAT: %s", notecardManager.rat);
        lv_label_set_text(ui_s3_LabelRat, text_buffer);

        sprintf(text_buffer, "Band: %s", notecardManager.band);
        lv_label_set_text(ui_s3_LabelBand, text_buffer);

        // fill in ui_BarX depending on reported bars
        if (notecardManager.bars > 0){
            lv_bar_set_value(ui_s3_Bar1, 100, LV_ANIM_OFF);
        };
        if (notecardManager.bars > 1){
            lv_bar_set_value(ui_s3_Bar2, 100, LV_ANIM_OFF);
        };
        if (notecardManager.bars > 2){
            lv_bar_set_value(ui_s3_Bar3, 100, LV_ANIM_OFF);
        };
        if (notecardManager.bars > 3){
            lv_bar_set_value(ui_s3_Bar4, 100, LV_ANIM_OFF);
        };

        lv_textarea_set_text(ui_s3_TextAreaHubStatus, notecardManager.hub_status);
        lv_textarea_set_text(ui_s3_TextAreaSyncStatus, notecardManager.hub_sync_status);

        if (notecardManager.serviceTick){
            lv_obj_clear_state(ui_s3_Button_Refresh, LV_STATE_CHECKED);
            lv_obj_add_state(ui_s3_Button_Refresh, LV_STATE_DISABLED);
        } else {
            lv_obj_clear_state(ui_s3_Button_Refresh, LV_STATE_DISABLED);
            lv_obj_add_state(ui_s3_Button_Refresh, LV_STATE_CHECKED);
        }
    }
}

void display_sensor_info(lv_timer_t * timer){

    if (lv_scr_act() == ui_Screen6 )
    {
        // gather the ui objects into arrays for easier looping
        lv_obj_t *s6_values[8] = {
            ui_s6_value1,
            ui_s6_value2,
            ui_s6_value3,
            ui_s6_value4,
            ui_s6_value5,
            ui_s6_value6,
            ui_s6_value7,
            ui_s6_value8
        };

        lv_obj_t *s6_names[8] = {
            ui_s6_name1,
            ui_s6_name2,
            ui_s6_name3,
            ui_s6_name4,
            ui_s6_name5,
            ui_s6_name6,
            ui_s6_name7,
            ui_s6_name8
        };

        lv_obj_t *s6_bars[8] = {
            ui_s6_bar1,
            ui_s6_bar2,
            ui_s6_bar3,
            ui_s6_bar4,
            ui_s6_bar5,
            ui_s6_bar6,
            ui_s6_bar7,
            ui_s6_bar8
        };

        const char* key;
        int i = 0;

        for (auto& keyval : inputData.biofilterTemperatureData) {
            key = const_cast<char*>(keyval.first.c_str());
            sprintf(text_buffer, "%0.1f %%", keyval.second);
            lv_label_set_text(s6_values[i], text_buffer);
            lv_label_set_text(s6_names[i], key);
            lv_bar_set_value(s6_bars[i], keyval.second, LV_ANIM_OFF);
            lv_bar_set_range(s6_bars[i], 0, 14);
            i++;
            if (i >= 8) break;
        }


    }

    if (lv_scr_act() == ui_Screen7 )
    {
        // gather the ui objects into arrays for easier looping
        lv_obj_t *s7_values[8] = {
            ui_s7_value1,
            ui_s7_value2,
            ui_s7_value3,
            ui_s7_value4,
            ui_s7_value5,
            ui_s7_value6,
            ui_s7_value7,
            ui_s7_value8
        };

        lv_obj_t *s7_names[8] = {
            ui_s7_name1,
            ui_s7_name2,
            ui_s7_name3,
            ui_s7_name4,
            ui_s7_name5,
            ui_s7_name6,
            ui_s7_name7,
            ui_s7_name8
        };

        lv_obj_t *s7_bars[8] = {
            ui_s7_bar1,
            ui_s7_bar2,
            ui_s7_bar3,
            ui_s7_bar4,
            ui_s7_bar5,
            ui_s7_bar6,
            ui_s7_bar7,
            ui_s7_bar8
        };

        const char* key;
        int i = 0;
        for (auto& keyval : inputData.gasData) {
            key = const_cast<char*>(keyval.first.c_str());
            sprintf(text_buffer, "%0.1f %", keyval.second);
            lv_label_set_text(s7_values[i], text_buffer);
            lv_label_set_text(s7_names[i], key);
            lv_bar_set_value(s7_bars[i], keyval.second, LV_ANIM_OFF);
            lv_bar_set_range(s7_bars[i], 0, 50);
            i++;
            if (i >= 8) break;
        }

        key = "GasFlow";
        sprintf(text_buffer, "%0.1f", inputData.flowData[key]);
        lv_label_set_text(s7_values[i], text_buffer);
        lv_label_set_text(s7_names[i], "GasFlow (ml/min)");
        lv_bar_set_value(s7_bars[i], inputData.flowData[key], LV_ANIM_OFF);
        lv_bar_set_range(s7_bars[i], 0, 1200);
        i++;

        for (auto& keyval : inputData.pHData) {
            key = const_cast<char*>(keyval.first.c_str());
            sprintf(text_buffer, "pH %0.1f", keyval.second);
            lv_label_set_text(s7_values[i], text_buffer);
            lv_label_set_text(s7_names[i], key);
            lv_bar_set_value(s7_bars[i], keyval.second, LV_ANIM_OFF);
            lv_bar_set_range(s7_bars[i], 0, 14);
            i++;
            if (i >= 8) break;
        }
    }

    if (lv_scr_act() == ui_Screen8 )
    {
        // gather the ui objects into arrays for easier looping
        lv_obj_t *s8_values[8] = {
            ui_s8_value1,
            ui_s8_value2,
            ui_s8_value3,
            ui_s8_value4,
            ui_s8_value5,
            ui_s8_value6,
            ui_s8_value7,
            ui_s8_value8
        };

        lv_obj_t *s8_names[8] = {
            ui_s8_name1,
            ui_s8_name2,
            ui_s8_name3,
            ui_s8_name4,
            ui_s8_name5,
            ui_s8_name6,
            ui_s8_name7,
            ui_s8_name8
        };

        lv_obj_t *s8_bars[8] = {
            ui_s8_bar1,
            ui_s8_bar2,
            ui_s8_bar3,
            ui_s8_bar4,
            ui_s8_bar5,
            ui_s8_bar6,
            ui_s8_bar7,
            ui_s8_bar8
        };

        const char* key;
        int i = 0;
        for (auto& keyval : inputData.temperatureData) {
            key = const_cast<char*>(keyval.first.c_str());
            sprintf(text_buffer, "%0.1f C", keyval.second);
            lv_label_set_text(s8_values[i], text_buffer);
            lv_label_set_text(s8_names[i], key);
            lv_bar_set_value(s8_bars[i], keyval.second, LV_ANIM_OFF);
            i++;
            if (i >= 8) break;
        }
    }

    if (lv_scr_act() == ui_Screen9 )
    {
        // gather the ui objects into arrays for easier looping
        lv_obj_t *s9_values[8] = {
            ui_s9_value1,
            ui_s9_value2,
            ui_s9_value3,
            ui_s9_value4,
            ui_s9_value5,
            ui_s9_value6,
            ui_s9_value7,
            ui_s9_value8
        };

        lv_obj_t *s9_names[8] = {
            ui_s9_name1,
            ui_s9_name2,
            ui_s9_name3,
            ui_s9_name4,
            ui_s9_name5,
            ui_s9_name6,
            ui_s9_name7,
            ui_s9_name8
        };

        lv_obj_t *s9_bars[8] = {
            ui_s9_bar1,
            ui_s9_bar2,
            ui_s9_bar3,
            ui_s9_bar4,
            ui_s9_bar5,
            ui_s9_bar6,
            ui_s9_bar7,
            ui_s9_bar8
        };

        const char* key;
        int i = 0;

        key = "Power";
        sprintf(text_buffer, "%0.1f", inputData.powerData[key]);
        lv_label_set_text(s9_values[i], text_buffer);
        lv_label_set_text(s9_names[i], "Power (Watts)");
        lv_bar_set_value(s9_bars[i], inputData.flowData[key], LV_ANIM_OFF);
        lv_bar_set_range(s9_bars[i], 0, 4000);
        i++;

        key = "Energy";
        sprintf(text_buffer, "%0.1f", inputData.powerData[key]);
        lv_label_set_text(s9_values[i], text_buffer);
        lv_label_set_text(s9_names[i], "Energy (kWh)");
        lv_bar_set_value(s9_bars[i], inputData.flowData[key], LV_ANIM_OFF);
        lv_bar_set_range(s9_bars[i], 0, 100);
        i++;

        // key = "WaterFlow";
        // sprintf(text_buffer, "%0.1f", inputData.flowData[key]);
        // lv_label_set_text(s9_values[i], text_buffer);
        // lv_label_set_text(s9_names[i], "WaterFlow (l/min)");
        // lv_bar_set_value(s9_bars[i], inputData.flowData[key], LV_ANIM_OFF);
        // lv_bar_set_range(s9_bars[i], 0, 8);
        // i++;

        // key = "BatteryVoltage";
        // sprintf(text_buffer, "%0.1f", inputData.powerData[key]);
        // lv_label_set_text(s9_values[i], text_buffer);
        // lv_label_set_text(s9_names[i], key);
        // lv_bar_set_value(s9_bars[i], inputData.powerData[key], LV_ANIM_OFF);
        // lv_bar_set_range(s9_bars[i], 0, 5);
        // i++;

        // key = "BatteryCurrent";
        // sprintf(text_buffer, "%0.1f", inputData.powerData[key]);
        // lv_label_set_text(s9_values[i], text_buffer);
        // lv_label_set_text(s9_names[i], key);
        // lv_bar_set_value(s9_bars[i], inputData.powerData[key], LV_ANIM_OFF);
        // lv_bar_set_range(s9_bars[i], 0, 8);
        // i++;
        // key = "BatteryLevel";
        // sprintf(text_buffer, "%0.1f", inputData.powerData[key]);
        // lv_label_set_text(s9_values[i], text_buffer);
        // lv_label_set_text(s9_names[i], key);
        // lv_bar_set_value(s9_bars[i], inputData.powerData[key], LV_ANIM_OFF);
        // lv_bar_set_range(s9_bars[i], 0, 100);
        // i++;

        for (auto& keyval : inputData.moistureData) {
            key = const_cast<char*>(keyval.first.c_str());
            sprintf(text_buffer, "%0.1f %%", keyval.second);
            lv_label_set_text(s9_values[i], text_buffer);
            lv_label_set_text(s9_names[i], key);
            lv_bar_set_value(s9_bars[i], keyval.second, LV_ANIM_OFF);
            lv_bar_set_range(s9_bars[i], 0, 14);
            i++;
            if (i >= 8) break;
        }


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
    lv_label_set_text(ui_s1_headerTime, time_str);
    lv_label_set_text(ui_s2_headerTime, time_str);
    lv_label_set_text(ui_s3_headerTime, time_str);
    lv_label_set_text(ui_s4_headerTime, time_str);
    // lv_label_set_text(ui_s5_headerTime, time_str);
    lv_label_set_text(ui_s6_headerTime, time_str);
    lv_label_set_text(ui_s7_headerTime, time_str);
    lv_label_set_text(ui_s8_headerTime, time_str);
    lv_label_set_text(ui_s9_headerTime, time_str);

    // display boot time
    char * time_str_temp;
    char time_str_boot[64];
    time_str_temp = lv_label_get_text(ui_s5_headerTime);
    if (strcmp("--:--:--", time_str_temp) == 0){
        sprintf(time_str_boot, "boot time: %s", time_str);
        lv_label_set_text(ui_s5_headerTime, time_str_boot);
    }
    // strftime(time_str, sizeof(time_str), "%Y-%m-%d %X", time_info);

}

void display_log(lv_timer_t * timer){
    if (lv_scr_act() == ui_Screen5){ 
        lv_textarea_set_text(ui_s5_TextAreaLog, logBuffer);
    }
}

static void gas_sample_go_event_cb(lv_event_t * e)
{
    // changeEnvVar("gasSampleNow", "1");
    stateMachine.envVars["gasSampleNow"] = 1;
}

static void gas_sample_stop_event_cb(lv_event_t * e)
{
    // changeEnvVar("gasSampleStop", "1");
    stateMachine.envVars["gasSampleStop"] = 1;
}

static void gas_sample_time_text_event_cb(lv_event_t * e)
{
    lv_obj_t * ta = lv_event_get_target(e);
    const char * txt = lv_textarea_get_text(ta);

    // if a character has just been added (rather than deleted)
    // we need to cut it to 5 characters appropriately and let the callback run again.
    if(strlen(txt) > 5) {
        //if we are not at the end, overtype what is there
        if (lv_textarea_get_cursor_pos(ta) < 6){
            lv_textarea_del_char_forward(ta);
            return;
        }
        else{
        // if the string is complete, don't accept more input
            lv_textarea_del_char(ta);
            return;
        }
    }
        
    //validate the first two characters make a number less than 24
    //Note this doesn't catch the case where the characters are --:--
    txt = lv_textarea_get_text(ta);
    int num;
    char hr_str[3] = {txt[0], txt[1], '\0'};
    num = atoi(hr_str);

    if (num > 23) {
        gas_sample_selected_event_cb(e);
        Serial.println("Invalid hour time");
    }

    char min_str[3] = {txt[3], txt[4], '\0'};
    num = atoi(min_str);

    if (num > 59) {
        gas_sample_selected_event_cb(e);
        Serial.println("Invalid minute time");
    }

    //if cursor position is 2, then skip over the colon to 3
    if(lv_textarea_get_cursor_pos(ta) == 2) {
        lv_textarea_set_cursor_pos(ta, 3);
    }

    if((lv_textarea_get_cursor_pos(ta) == 5)
        && (strlen(txt) == 5)
        && (txt[4] != '-'))
        {
        lv_obj_clear_state(ta, LV_STATE_FOCUSED);
        ESP_LOGI("GUI", "Time string is complete, parsing");

        if (ta == ui_s2_Time1){
            myEnvVarCb("sampleTime1_hour", hr_str, NULL);
            myEnvVarCb("sampleTime1_min", min_str, NULL);
        }
        else if (ta == ui_s2_Time2){
            myEnvVarCb("sampleTime2_hour", hr_str, NULL);
            myEnvVarCb("sampleTime2_min", min_str, NULL);
        }
        else if (ta == ui_s2_Time3){
            myEnvVarCb("sampleTime3_hour", hr_str, NULL);
            myEnvVarCb("sampleTime3_min", min_str, NULL);
        }
        else if (ta == ui_s2_Time4){
            myEnvVarCb("sampleTime4_hour", hr_str, NULL);
            myEnvVarCb("sampleTime4_min", min_str, NULL);
        }
        refreshEnvironment();
    }
}

static void gas_sample_selected_event_cb(lv_event_t * e)
{
    lv_obj_t * ta = lv_event_get_target(e);
    const char * txt = "--:--";

    lv_keyboard_set_textarea(ui_s2_Keyboard, ta);
    lv_textarea_set_accepted_chars(ta, "0123456789:-");
    lv_textarea_set_text(ta, txt);
    lv_textarea_set_cursor_pos(ta, 0);
    lv_obj_add_state(ta, LV_STATE_FOCUSED);
}