#include <M5Unified.h>
#include <gob_unifiedButton.hpp>

#include "MODULE_4IN8OUT.h"
#include "config.h"

MODULE_4IN8OUT module;

#define MODULE_4IN8OUT_START_ADDRESS 0x45
#define MODULE_4IN8OUT_NEW_ADDRESS 0x46

goblib::UnifiedButton unifiedButton;


char buffer[100];

void setup() {
    M5.begin();  // Init M5Stack.
    unifiedButton.begin(&M5.Display);
    Wire1.begin(PIN_SDA_I2C_SYS, PIN_SCL_I2C_SYS, 400000);  //Init I2C_SYS

    while (!module.begin(&Wire1, PIN_SDA_I2C_SYS, PIN_SCL_I2C_SYS, MODULE_4IN8OUT_START_ADDRESS)) {
        Serial.println("4IN8OUT INIT ERROR");
        M5.Lcd.println("4IN8OUT INIT ERROR");
        delay(1000);
    };
    Serial.println("4IN8OUT INIT SUCCESS");
}

void loop() {
    M5.Lcd.drawString("4IN8OUT MODULE", 60, 80, 4);
    M5.Lcd.drawString("FW VERSION:" + String(module.getVersion()), 70, 120, 4);

    sprintf(buffer, "Click BtnB Update Addr to 0x%0X", MODULE_4IN8OUT_NEW_ADDRESS);
    M5.Lcd.drawString(buffer, 60, 160, 2);

    
    if (M5.BtnB.wasPressed()) {
        if (module.setDeviceAddr(MODULE_4IN8OUT_NEW_ADDRESS)) {
            sprintf(buffer, "Update Address: 0x%0X success", MODULE_4IN8OUT_NEW_ADDRESS);
            Serial.println(buffer);
            M5.Lcd.drawString(buffer, 60, 30, 2);
        }
    }
    M5.update();
    unifiedButton.update();
    unifiedButton.draw();
}
