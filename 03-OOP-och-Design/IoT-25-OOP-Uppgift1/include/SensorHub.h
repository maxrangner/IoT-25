#pragma once
#include <vector>
#include "Sensor.h"
#include "TemperatureSensor.h"

class SensorHub {
    std::vector<Sensor*> mySensors;
public:
    void addSensor();
    void removeSensor(int id);
    void printAllInfo();
};