#include <Arduino.h>
#include <unordered_map>
#include <Notecard.h>

void JAddMapToObject(J *obj, std::unordered_map<std::string, float> map){

    for (auto& keyval : map) {
        if (!isnan(keyval.second)) {
            char buffer[12];
            dtostrf(keyval.second, 0, 2, buffer);
            JAddStringToObject(obj,
                const_cast<char*>(keyval.first.c_str()),
                buffer);
        }
    }
}   

std::unordered_map<std::string, float> testData = {
        {"paramA", 1},
        {"paramB", 2},
    };

Notecard notecard;
J *queue;


void setup() {
    Serial.begin();
    while (!Serial) {;}
    Serial.println("USB Serial Started");

    Wire.begin();

    notecard.begin(NOTE_I2C_ADDR_DEFAULT, NOTE_I2C_MAX_DEFAULT, Wire);

    queue = JCreateObject();

} 

void loop() {

    char timestr[12];
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int unixTime = tv.tv_sec;
    sprintf(timestr, "%d", unixTime);


    J *entry = JCreateObject();
    JAddMapToObject(entry, testData);
    JAddItemToObject(queue, timestr, entry);

    char *reqStr = JConvertToJSONString(queue);

    if (reqStr == NULL) {
        Serial.println("Error converting to JSON");
    }
    else {
        Serial.printf("Queue: %s\n\n", reqStr);
    }

    vTaskDelay(5000 / portTICK_PERIOD_MS);


}

