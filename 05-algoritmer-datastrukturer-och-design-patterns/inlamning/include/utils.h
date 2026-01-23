#ifndef SYSTEMFUNCTIONS_H
#define SYSTEMFUNCTIONS_H
#include "EventLog.h"
#include "EventQueue.h"

typedef struct {
    int sensorId;
    sensorType type;
    char* unit;
} Sensor;

void generateRandomEvent(Event* newEvent, timestamp* timeTicks, int sensorType);
const char* enumToChar(sensorType type);

#endif