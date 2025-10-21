#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

constexpr int NUM_DATAPOINTS = 5;

enum sensorTypes{
    noType, // 0.
    temperatureSensor, // 1.
    humiditySensor, // 2.
    lightSensor, // 3.
    movementSensor, // 4.
};

enum MenuSelection {
    startofMenu, // 0.
    addSensor, // 1.
    collectReadings, // 2.
    dispData, // 3.
    save, // 4.
    load, // 5.
    quit, // 8.
    endOfMenu
};

enum validatorType {
    wholeNum = 1, // 1.
    decimalNum, // 2.
    text // 3.
};

struct DataPoint {
    int deviceId {};
    int type;
    float value {};
    bool isActive = true;
    bool isTriggered = false;
    DataPoint() : deviceId(0), type(0), value(0.0f), isActive(true), isTriggered(false) {}
    DataPoint(int id, int t, float v, bool a, bool tr)
        : deviceId(id), type(t), value(v), isActive(a), isTriggered(tr) {}
};

#endif