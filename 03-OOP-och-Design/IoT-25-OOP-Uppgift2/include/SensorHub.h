#pragma once
#include <vector>
#include <memory>
#include "Sensor.h"
#include "definitions.h"

class SensorHub {
    std::vector<std::unique_ptr<Sensor>> mySensors;
public:
    void addSensor(SensorType type);
    void removeSensor(int id);
    void printAllInfo();
    const std::vector<std::unique_ptr<Sensor>>& getSensorsList() const;
};