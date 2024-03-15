#include <M5Unified.h>
#include "config.h"
#include <gob_unifiedButton.hpp>

goblib::UnifiedButton unifiedButton;


char buffer[100];
    
void setup() {
    
    M5.begin();
    M5.Display.setBrightness(100);

    unifiedButton.begin(&M5.Display);


    //Default is just boost enabled (so can start from battery), AKA POWER_MODE_USB_IN_BUS_IN
    M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b10000000, 100000L);  // BOOST_EN = 0
    // M5.In_I2C.bitOn(AW9523_ADDR, 0x03, 0b10000000, 100000L);  // BOOST_EN = 1

    M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00000010, 100000L);  // BUS_OUT_EN = 0
    // M5.In_I2C.bitOn(AW9523_ADDR, 0x02, 0b00000010, 100000L);  // BUS_OUT_EN = 1

    M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00100000, 100000L);  // USB_OTG_EN = 0
    // M5.In_I2C.bitOn(AW9523_ADDR, 0x02, 0b00100000, 100000L);  // USB_OTG_EN = 1

    //Power Saving Options
    setCpuFrequencyMhz(240);
    M5.Display.setBrightness(100);

    M5.In_I2C.bitOn(AW9523_ADDR, 0x02, 0b00000001, 100000L);  // TOUCH_RST = 1
    // M5.In_I2C.bitOn(AW9523_ADDR, 0x02, 0b00000100, 100000L);  // AW_RST = 1
    // M5.In_I2C.bitOn(AW9523_ADDR, 0x03, 0b00000001, 100000L);  // CAM_RST = 1
    M5.In_I2C.bitOn(AW9523_ADDR, 0x03, 0b00000010, 100000L);  // LCD_RST = 1

    // M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00000001, 100000L);  // TOUCH_RST = 0 // Touch Off
    M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00000100, 100000L);  // AW_RST = 0 // Audio Amp Off
    M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b00000001, 100000L);  // CAM_RST = 0 //Camera Off
    // M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b00000010, 100000L);  // LCD_RST = 0 //Screen OFF

    M5.Power.setUsbOutput(false);
    M5.Power.setExtOutput(false);
    M5.Power.setBatteryCharge(false);
    M5.Power.setLed(0);

}


void loop() {

    sprintf(buffer, "Click BtnA to set cpu to 80Mhz");
    M5.Lcd.drawString(buffer, 60, 80, 2);

    sprintf(buffer, "Click BtnB to Deepsleep for 10s");
    M5.Lcd.drawString(buffer, 60, 120, 2);

    sprintf(buffer, "Click BtnC to Timersleep for 10s");
    M5.Lcd.drawString(buffer, 60, 160, 2);


    if (M5.BtnA.wasPressed()) {
        
        setCpuFrequencyMhz(80);
        
        M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00000001, 100000L);  // TOUCH_RST = 0 // Touch Off
        M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00000100, 100000L);  // AW_RST = 0 // Audio Amp Off
        M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b00000001, 100000L);  // CAM_RST = 0 //Camera Off
        M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b00000010, 100000L);  // LCD_RST = 0 //Screen OFF

        M5.Power.setUsbOutput(false);
        M5.Power.setExtOutput(false);
        M5.Power.setBatteryCharge(false);
        M5.Power.setLed(0);
        M5.Display.setBrightness(0);


    }

    if (M5.BtnB.wasPressed()) {
        
        M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00000001, 100000L);  // TOUCH_RST = 0 // Touch Off
        M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00000100, 100000L);  // AW_RST = 0 // Audio Amp Off
        M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b00000001, 100000L);  // CAM_RST = 0 //Camera Off
        M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b00000010, 100000L);  // LCD_RST = 0 //Screen OFF

        M5.Power.setUsbOutput(false);
        M5.Power.setExtOutput(false);
        M5.Power.setBatteryCharge(false);
        M5.Power.setLed(0);
        
        M5.Display.setBrightness(0);

        M5.Power.deepSleep(10*1000000);
    }

    if (M5.BtnC.wasPressed()) {
        
        M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00000001, 100000L);  // TOUCH_RST = 0 // Touch Off
        M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b00000100, 100000L);  // AW_RST = 0 // Audio Amp Off
        M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b00000001, 100000L);  // CAM_RST = 0 //Camera Off
        M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b00000010, 100000L);  // LCD_RST = 0 //Screen OFF

        M5.Power.setUsbOutput(false);
        M5.Power.setExtOutput(false);
        M5.Power.setBatteryCharge(false);
        M5.Power.setLed(0);
        
        M5.Display.setBrightness(0);

        M5.Power.timerSleep(10);


    }
    M5.update();
    unifiedButton.update();
    unifiedButton.draw();

}