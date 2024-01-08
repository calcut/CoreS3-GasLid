#include "inputs.h"

Inputs inputs;

void Inputs::init(void){

    USBSerial.println("\n**** Mod_a1019 init ****");
    
    vTaskDelay(20 / portTICK_PERIOD_MS);
    mod_a1019.init();
    vTaskDelay(20 / portTICK_PERIOD_MS);
    mod_evd.init();
    vTaskDelay(20 / portTICK_PERIOD_MS);
    if (gpioExpander.begin() == false) {
        USBSerial.println("Check Connections. No I2C GPIO Expander detected.");
    }

    bool pinModes[8] = {GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN, GPIO_IN};
    gpioExpander.pinMode(pinModes);
}

void Inputs::pollSensorData(void){
    float tc[8];
    float evd_sensors[4];
    float voltage;
    mod_a1019.readTC_float(tc);
    // Delay seems to be needed to prevent Modbus errors
    // It fails at around 3ms or faster. So setting to 20ms
    vTaskDelay(20 / portTICK_PERIOD_MS);
    mod_evd.getSensors(evd_sensors);
    vTaskDelay(20 / portTICK_PERIOD_MS);
    voltage = mod_sdm120.readRegister(SDM120_VOLTAGE);

    powerData["P1_Supply"] = mod_sdm120.readRegister(SDM120_APPARENT_POWER);
    temperatureData["Tr1_CompressorOut"]    = tc[0];
    temperatureData["Tr2_CondenserOut"]     = tc[1];
    temperatureData["Tr3_FlexStore"]        = tc[2];
    temperatureData["Tr4_Evaporator"]       = tc[3];
    temperatureData["Tr5_CompressorIn"]     = tc[4];
    temperatureData["Tw1_DHWReturn"]        = tc[5];
    temperatureData["Tw2_DHWFlow"]          = tc[6];
    temperatureData["Tw3_FlexStore"]        = tc[7];
}

void Inputs::pollPhysicalControls(void){

    USBSerial.print("Polling physical controls\n");

    bool gpioStatus[8];
    uint8_t gpioval;
    gpioval = gpioExpander.digitalReadPort(gpioStatus);

    USBSerial.println(gpioval, BIN);
    if (gpioStatus[1] == 1){
        physicalControls.handOffAuto = AUTO;
    }
    else if (gpioStatus[0] == 1){
        physicalControls.handOffAuto = HAND;
    }
    else {
        physicalControls.handOffAuto = OFF;
    }

    if (gpioStatus[7] == 1){
        physicalControls.manualState = DISCHARGING;
    }
    else if (gpioStatus[6] == 1){
        physicalControls.manualState = DEFROST;
    }
    else {
        physicalControls.manualState = CHARGING;
    }

    USBSerial.printf("HandOffAuto: %i, ManualState: %i\n", physicalControls.handOffAuto, physicalControls.manualState);
    // physicalControls.handOffAuto = HAND;
    // physicalControls.manualState = CHARGING;
}

void Inputs::serviceFlowMeters(void){

    pcnt_get_counter_value(PCNT_UNIT_0, &counterVal);

    if (millis() - previousPulseTime != 0){
        flowPPS = ((counterVal - previousPulseCount)*1000)/(millis() - previousPulseTime);
        inputs.flowData["Fl1_DHW_lpm"] = flowPPS * 60 / 4600; //4600 pulses per litre
    }

    previousPulseCount = counterVal;
    previousPulseTime = millis();
    
}

void Inputs::initFlowMeters(int pin){
    pcnt_config_t pcntCh1 = {
        .pulse_gpio_num = pin,
        .ctrl_gpio_num = PCNT_PIN_NOT_USED,
        .lctrl_mode = PCNT_MODE_KEEP,
        .hctrl_mode = PCNT_MODE_KEEP,
        .pos_mode = PCNT_COUNT_DIS,
        .neg_mode = PCNT_COUNT_INC,
        .counter_h_lim = 32767,
        .counter_l_lim = -32768,
        .unit = PCNT_UNIT_0,
        .channel = PCNT_CHANNEL_0,
    };
    pcnt_unit_config(&pcntCh1);
    pcnt_counter_clear(PCNT_UNIT_0);
    USBSerial.printf("Flow meter initialised on pin %d\n", pin);
}