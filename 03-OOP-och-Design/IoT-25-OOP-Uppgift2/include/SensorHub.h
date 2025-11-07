#pragma once
#include <vector>
#include <memory>
#include "Sensor.h"
#include "Logger.h"
#include "definitions.h"

class SensorHub {
    std::vector<std::unique_ptr<Sensor>> mySensors;
public:
    SensorHub();
    SensorHub(Logger& connectedLogger);
    void addSensor(SensorType type);
    void removeSensor(int id);
    void updateSensors(std::vector<int> sensors = {});
    void printAllInfo();
    const std::vector<std::unique_ptr<Sensor>>& getSensorsList() const;
};