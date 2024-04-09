#ifndef NOTECARD_MANAGER_H
#define NOTECARD_MANAGER_H

#ifndef DFU_ENABLE
#define DFU_ENABLE false
#endif

#include <Arduino.h>
#include <Notecard.h>
#include <unordered_map>
#include "NotecardEnvVarManager.h"
#include "config.h"

void JAddFloatMapToObject(J *obj, std::unordered_map<std::string, float> map);

class NotecardManager {

    private:
        Notecard notecard;
        uint32_t env_modified_time = 0;
        esp_err_t err;
        
    public:
        NotecardManager();
        NotecardEnvVarManager *envVarManager = NULL;
        void begin();
        void softAP();
        void getWifiConnection();
        void clearWifiConnection();
        void init(const char *uid, const char *mode, int inbound, int outbound, bool sync);
        void configureOutboardDFU();
        esp_err_t hubGet();
        void hubStatus();
        void hubSyncStatus();
        void cardStatus();
        void cardWireless();
        void cardWirelessPenaltyReset();
        void getEnvironment();
        void setEnvironmentVar(const char *name, const char * text);
        void deleteEnvironmentVar(const char *name);
        void setDefaultEnvironmentVar(const char *name, const char * text);
        void getTime();
        void sendSensorData(std::unordered_map<std::string, float> DataMap, int timestamp);
        void appendToQueue(std::unordered_map<std::string, float> floatMap, int timestamp);
        void sendQueuedSensorData(void);

        bool connected;
        bool newEnvVars = false;
        int bars;
        int rssi;
        char rat[8];
        char deviceUID[20];
        char sn[20];
        char band[20];
        char hub_status[64];
        char hub_sync_status[64];
        int epoch_time = 0;
        int utc_offset_minutes = 0;
        bool serviceEnabled = false;
        bool serviceTick = false;
        J *queue;
        
        std::unordered_map<std::string, int> envVars = {
            {"serviceInterval_s", 10},
            {"timeSyncInterval_s", 10},
            {"noteSendInterval_s", 60},
            {"noteSampleInterval_s", 15},
        };
};

extern NotecardManager notecardManager;


#endif