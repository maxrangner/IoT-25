#pragma once
#include <map>
#include <vector>
#include "definitions.h"

class Logger {
    std::map<time_t, std::vector<Measurement>> log;

public:
    void addMeasurments(time_t timestamp, std::vector<Measurement> measurements);
};