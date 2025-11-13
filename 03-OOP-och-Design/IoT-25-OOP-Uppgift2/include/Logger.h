#pragma once
#include <map>
#include <vector>
#include <mutex>
#include <array>
#include "Display.h"
#include "definitions.h"

class Logger {
    Display* connectedDisplay;
    std::vector<Measurement> log;
    std::mutex logMutex;
public:
    Logger(Display& display);
    void printLog();
    void addMeasurment(Measurement measurement);
    std::vector<Measurement>& getLog();
    std::array<Measurement, 10> getGraphData(int sensorId);
};