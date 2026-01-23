#include "utils.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stdio.h"
#include "time.h"
#include "Event.h"
#include "EventQueue.h"
#include "EventLog.h"

static int nextSensorId = 0;

typedef struct {
    int sensorId;
    sensorType type;
    char* unit;
} Sensor;

Sensor sensorList[] = {
    {.sensorId = 0, .type = TEMPERATURE, .unit = "c"},
    {.sensorId = 1, .type = HUMIDITY, .unit = "c"},
    {.sensorId = 2, .type = LUMINANCE, .unit = "c"}
};

/********************************************************
************************ UTILS **************************
********************************************************/ 

void generateRandomEvent(Event* newEvent, int sensorType) {
    long long randomTime = time(NULL) - (rand() % 86400); // 86400 == seconds in a day
    (*newEvent).timeLogged = randomTime;
    (*newEvent).sensorId = sensorList[sensorType].sensorId;
    (*newEvent).sensorType = sensorList[sensorType].type;
    float tempValue;
    int minVal;
    int maxVal;
    switch ((*newEvent).sensorType) {
        case 0: // TEMPERATURE
            minVal = 10;
            maxVal = 35;
            tempValue = (rand() % ((maxVal - minVal) * 100)); // Scale up to force the value to include two decimals
            tempValue /= 100; // Scale down to correct decimal range
            tempValue += minVal; // Set value to correct starting point
            break;
        case 1: // HUMIDITY
            minVal = 30;
            maxVal = 90;
            tempValue = (rand() % ((maxVal - minVal) * 100));
            tempValue /= 100;
            tempValue += minVal;
            break;
        case 2: // LUMINANCE
            minVal = 0;
            maxVal = 10000;
            tempValue = (rand() % ((maxVal - minVal) / 100));
            tempValue *= 100;
            tempValue += minVal;
            break;
        default: // UNNKOWN
            tempValue = 0;
            break;
    }
    (*newEvent).value = tempValue;
}
