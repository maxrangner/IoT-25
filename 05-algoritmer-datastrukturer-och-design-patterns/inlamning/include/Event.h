#ifndef EVENT_H
#define EVENT_H
#include <time.h>

typedef time_t timestamp;
typedef int sensorId;
typedef float sensorValue;

typedef enum sensorType {
    TEMPERATURE,
    HUMIDITY,
    LUMINANCE,
    UNKNOWN
} sensorType;

typedef struct Event {
    timestamp timeLogged;
    int sensorId;
    sensorType sensorType;
    sensorValue value;
} Event;

#endif