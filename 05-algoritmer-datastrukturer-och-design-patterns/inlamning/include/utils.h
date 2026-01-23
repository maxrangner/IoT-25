#ifndef SYSTEMFUNCTIONS_H
#define SYSTEMFUNCTIONS_H
#include "EventLog.h"
#include "EventQueue.h"

typedef struct {
    int sensorId;
    sensorType type;
    char* unit;
} Sensor;

void generateRandomEvent(Event* newEvent, int sensorType);

#endif