#pragma once
#include <vector>
#include <memory>
#include "Sensor.h"
#include "Logger.h"
#include "definitions.h"
#include "Logger.h"

class SensorHub {
    std::vector<std::unique_ptr<Sensor>> mySensors;
    Logger* connectedLog;
public:
    SensorHub(Logger& log);
    void addSensor(SensorType type);
    void removeSensor(int id);
    void readAllSensors(std::vector<int> sensors = {});
    const std::vector<std::unique_ptr<Sensor>>& getSensorsList() const;
};