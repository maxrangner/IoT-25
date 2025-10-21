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

struct DataPoint {
    int deviceId {};
    int type;
    float value {};
    bool isActive = true;
    bool isTriggered = false;
};

#endif