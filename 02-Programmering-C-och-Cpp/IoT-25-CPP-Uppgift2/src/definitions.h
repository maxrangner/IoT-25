#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

constexpr int NUM_DATAPOINTS = 5;
constexpr int RANDOM_MIN = -100;
constexpr int RANDOM_MAX = 100;

enum sensorTypes : int{
    noType, // 0.
    temperatureSensor, // 1.
    humiditySensor, // 2.
    lightSensor, // 3.
    movementSensor, // 4.
};

enum MenuSelection : int {
    startofMenu, // 0.
    addSensor, // 1.
    removeSensor, // 2.
    collectReadings, // 3.
    dispData, // 4.
    save, // 5.
    load, // 6.
    quit, // 7.
    endOfMenu
};

enum validatorType : int {
    wholeNum = 1, // 1.
    decimalNum, // 2.
    text // 3.
};

struct DataPoint {
    int deviceId;
    int type;
    float value;
    bool isActive = true;
    bool isTriggered = false;
    DataPoint() : deviceId(0), type(0), value(0.0f), isActive(true), isTriggered(false) {}
    DataPoint(int id, int t, float v, bool a, bool tr)
        : deviceId(id), type(t), value(v), isActive(a), isTriggered(tr) {}
};

#endif