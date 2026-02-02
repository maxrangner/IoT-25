#include "utils.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stdio.h"
#include "time.h"
#include "Event.h"
#include "EventQueue.h"
#include "EventLog.h"
#include "Set.h"
#include "Context.h"
#include "observer.h"

Sensor sensorList[] = {
    {.sensorId = 0, .type = TEMPERATURE, .unit = "c"},
    {.sensorId = 1, .type = HUMIDITY, .unit = "%"},
    {.sensorId = 2, .type = LUMINANCE, .unit = "lx"}
};

/********************************************************
************************ UTILS **************************
********************************************************/ 

void generateRandomEvent(Event* newEvent, int sensorType) {
    (*newEvent).timeLogged = time(NULL); // time(NULL);
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

const char* sensorEnumToChar(sensorType type) {
    switch (type) {
        case 0: return "Temperature";
        case 1: return "Humidity";
        case 2: return "Luminance";
        default: return "Unknown";
    }
}

const char* getSensorSuffix(sensorType type) {
    switch (type) {
        case 0: return "c";
        case 1: return "%";
        case 2: return "lx";
        default: return "";
    }
}

void producer(Context* ctx, int timeOffset) {
    for (int s = 0; s < NUM_SENSOR_TYPES; s++) { 
        Event newEvent;
        generateRandomEvent(&newEvent, s); // s == sensorType 0: temp, 1: humid, 2: lux
        newEvent.timeLogged += timeOffset;
        if (queueEnqueue(ctx->queue, newEvent) == 0) break; // If queue is full, abort.
    }
}

void consumer(Context* ctx) {
    Event eventToLog;
    queueDequeue(ctx->queue, &eventToLog);
    notify(ctx, eventToLog);
}
