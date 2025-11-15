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
    Alarms alarms;
public:
    SensorHub(Logger& log);
    void addSensor(SensorType type);
    void removeSensor(int id);
    void restoreSensors();
    void readAllSensors(std::vector<int> sensors = {});
    const std::vector<std::unique_ptr<Sensor>>& getSensorsList() const;
    const Alarms& getAlarms() const;
    void setTemperatureAlarms(float low, float high);
    void setHumidityAlarms(float low, float high);
    void turnOffAlarms();
};