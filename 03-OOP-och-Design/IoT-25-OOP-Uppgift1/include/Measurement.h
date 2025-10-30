#pragma once
#include <string>

struct Measurement {
    int sensorId;
    std::string sensorType;
    std::string sensorUnit;
    float value;
    time_t timestamp;
};