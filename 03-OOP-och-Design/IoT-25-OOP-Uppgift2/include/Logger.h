#pragma once
#include <map>
#include <vector>
#include <mutex>
#include <array>
#include "Display.h"
#include "definitions.h"

class Logger {
    Display* connectedDisplay;
    std::map<time_t, std::vector<Measurement>> log;
    std::array<std::vector<Measurement>, 10> graphData;
    std::mutex logMutex;
public:
    Logger(Display& display);
    void addMeasurments(time_t timestamp, Measurement measurements);
    void printLog();
    std::vector<Measurement>& getLatestEntry();
    std::map<time_t, std::vector<Measurement>>& getLog();
    void updateGraphData(std::vector<Measurement> newMeasurement);
    std::array<std::vector<Measurement>, 10> getGraphData() const;
};