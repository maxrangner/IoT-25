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
    int updateInterval;
public:
    SensorHub(Logger& log);
    int getUpdateInterval() const;
    void addSensor(SensorType type);
    void removeSensor(int id);
    void updateSensors(std::vector<int> sensors = {});
    void printAllInfo();
    const std::vector<std::unique_ptr<Sensor>>& getSensorsList() const;
    void readAllSensors();
};