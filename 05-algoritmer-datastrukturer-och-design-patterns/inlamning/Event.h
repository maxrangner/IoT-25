#ifndef EVENT_H
#define EVENT_H
#include <time.h>

typedef struct tm timestamp;
typedef int sensorId;
typedef float sensorValue;

typedef enum sensorType {
    UNKNOWN,
    TEMPERATURE,
    HUMIDITY,
    MOTION
} sensorType;

typedef struct Event {
    timestamp timeLogged;
    int sensorId;
    sensorType sensorType;
    sensorValue value;
    int isTriggered;
} Event;

#endif