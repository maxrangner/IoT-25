#pragma once
#include <map>
#include <vector>
#include <mutex>
#include <array>
#include <fstream>
#include "Display.h"
#include "definitions.h"

class Logger {
    Display* connectedDisplay;
    std::vector<Measurement> log;
    std::mutex logMutex;
public:
    Logger(Display& display);

    // GETTERS
    std::vector<Measurement>& getLog();
    void printLog();

    // CORE
    void addMeasurment(Measurement measurement);
    std::array<Measurement, 10> getGraphData(int sensorId);

    // DATA STORAGE
    bool saveData();
    bool loadData();
};