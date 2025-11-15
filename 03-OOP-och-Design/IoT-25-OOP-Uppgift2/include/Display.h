#pragma once
#include <iostream>
#include <memory>
#include <mutex>
#include "Sensor.h"
#include "utils.h"

class Display {
    std::mutex logMutex;
public:
    void printMenu() const;
    void printHeader(const std::string& text) const;
    void printMessage(const std::string& text, bool lineBreak = true) const;
    void printMeasurement(const Measurement measurment) const;
    void printSensorsList(const std::vector<Measurement>& log, const std::vector<std::unique_ptr<Sensor>>& SensorsList, const Alarms& alarms) const;
    void printStats(std::vector<Measurement>& log);
    void printAlarms(const Alarms& alarms) const;
    void drawGraph(const std::array<Measurement, 10>& graphData) const;
    void clear() const;
};