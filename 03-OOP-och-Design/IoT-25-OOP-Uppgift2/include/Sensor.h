#pragma once
#include "Measurement.h"

class Sensor {
protected:
    int sensorId;
    std::string sensorType;
    std::string sensorUnit;

    float minMeasure;
    float maxMeasure; 
    bool isActive;

    static int nextId;
    int getNextId();
public:
    Sensor();
    void printInfo();
    int getSensorId() const;
    virtual Measurement read() = 0;
};