#ifndef NOTECARD_MANAGER_H
#define NOTECARD_MANAGER_H

#ifndef DFU_ENABLE
#define DFU_ENABLE false
#endif

#include <Arduino.h>
#include <Notecard.h>
#include <unordered_map>
#include "NotecardEnvVarManager.h"


class NotecardManager {

    private:
        Notecard notecard;
        uint32_t env_modified_time = 0;
        
    public:
        NotecardManager();
        NotecardEnvVarManager *envVarManager = NULL;
        void begin(Stream &serial_stream);
        void init(const char *uid, const char *mode, int inbound, int outbound, bool sync);
        void hubGet();
        void hubStatus();
        void hubSyncStatus();
        void cardStatus();
        void cardWireless();
        void getEnvironment();
        void setEnvironmentVar(char *name, char * text);
        void setDefaultEnvironmentVar(char *name, char * text);
        void getTime();
        bool connected;
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
        
        std::unordered_map<std::string, int> envVars = {
            {"serviceInterval_s", 10},
            {"timeSyncInterval_s", 10},
        };
};

extern NotecardManager notecardManager;

#endif