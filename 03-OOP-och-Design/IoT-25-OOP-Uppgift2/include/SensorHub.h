#pragma once
#include <vector>
#include <memory>
#include "Sensor.h"
#include "TemperatureSensor.h"

class SensorHub {
    std::vector<std::unique_ptr<Sensor>> mySensors;
public:
    void addSensor();
    void removeSensor(int id);
    void printAllInfo();
    const std::vector<std::unique_ptr<Sensor>>& SensorHub::getSensorsList() const;
};