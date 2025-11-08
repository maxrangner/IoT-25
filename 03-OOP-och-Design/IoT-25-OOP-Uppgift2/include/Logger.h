#pragma once
#include <map>
#include <vector>
#include <mutex>
#include "Display.h"
#include "definitions.h"

class Logger {
    Display* connectedDisplay;
    std::map<time_t, std::vector<Measurement>> log;
    std::mutex logMutex;
public:
    Logger(Display& display);
    void addMeasurments(time_t timestamp, Measurement measurements);
    void printLog();
};