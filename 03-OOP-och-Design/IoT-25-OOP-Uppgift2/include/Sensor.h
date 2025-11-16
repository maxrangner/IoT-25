#pragma once
#include <map>
#include "definitions.h"

class Sensor {
protected:
    // PROPERTIES
    int sensorId;
    SensorType sensorType;
    std::string sensorUnit;
    float minMeasure;
    float maxMeasure; 
    bool isActive_;

    // CORE
    static int nextId;
    int getNextId();
public:
    // CONSTRUCTOR
    Sensor();
    Sensor(int id);
    virtual ~Sensor() = default;

    //GETTERS
    void printInfo();
    int getSensorId() const;
    std::map<std::string, std::string> getInfo();

    // CORE
    virtual Measurement read() = 0;
    static void setNextId(int num);
};