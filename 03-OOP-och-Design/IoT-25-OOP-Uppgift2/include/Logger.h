#pragma once
#include <map>
#include <vector>
#include <mutex>
#include "definitions.h"

class Logger {
    std::map<time_t, std::vector<Measurement>> log;
    std::mutex logMutex;
public:
    void addMeasurments(time_t timestamp, Measurement measurements);
    void printLog();
};