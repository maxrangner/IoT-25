#ifndef UTILS_H
#define UTILS_H
#include "EventLog.h"
#include "EventQueue.h"

typedef struct Context Context;

typedef struct {
    int sensorId;
    sensorType type;
    char* unit;
} Sensor;

void generateRandomEvent(Event* newEvent, int sensorType);
const char* sensorEnumToChar(sensorType type);
const char* getSensorSuffix(sensorType type);
void producer(Context* ctx, int timeOffset);
void consumer(Context* ctx);

#endif