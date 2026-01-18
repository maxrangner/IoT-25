#include "systemFunctions.h"
#include <stdlib.h>
#include "stdio.h"
#include "time.h"
#include "Event.h"
#include "EventQueue.h"
#include "EventLog.h"

static int nextSensorId = 0;

/********************************************************
************************ MENU ***************************
********************************************************/ 

void printMenu() {
    // NOT IMPLEMENTED YET
}

void handleMenuInput() {
    // NOT IMPLEMENTED YET
}

void menu() {
    printMenu();
    handleMenuInput();
}

void printHelp() {
    // NOT IMPLEMENTED YET
}

void quit(EventLog* log, EventQueue* queue) {
    queueReset(queue);
    logDestroy(log);
}

/********************************************************
************************ UTILS **************************
********************************************************/ 

Event generateRandomEvent() {
    Event newEvent;
    newEvent.timeLogged = time(NULL);
    newEvent.sensorId = nextSensorId++;
    newEvent.sensorType = rand() % UNKNOWN; // Last entry in sensorType enum
    float tempValue;
    int minVal;
    int maxVal;
    switch (newEvent.sensorType) {
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
    newEvent.value = tempValue;
    return newEvent;
}

void tick(EventQueue* queue, EventLog* log, int iterations) {
    for (int i = 0; i < iterations; i++) {
        Event newEvent;
        newEvent = generateRandomEvent();
        queueEnqueue(queue, newEvent);
    }
    for (int i = 0; i < iterations; i++) {
        Event tempEvent;
        queueDequeue(queue, &tempEvent);
        logAppend(log, tempEvent);
    }
}

void sortLog(EventLog* log) {
    // NOT IMPLEMENTED YET
}

int findSensor(EventLog* log, int id) {
    // NOT IMPLEMENTED YET
}


