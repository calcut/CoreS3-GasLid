#include "notecard_manager.h"
#include "state_machine.h"
#include <unordered_map>

void myEnvVarCb(const char *key, const char *val, void *userCtx);
void setDefaultEnvironment(void);
void sendSensorData(std::unordered_map<std::string, float> DataMap);
void sendBatchSensorData();
// void sendQueuedSensorData(void);
void JAddFloatMapToObject(J *obj, std::unordered_map<std::string, float> map);