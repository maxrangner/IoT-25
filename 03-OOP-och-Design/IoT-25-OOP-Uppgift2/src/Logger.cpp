#include "Logger.h"

void Logger::addMeasurments(time_t timestamp, std::vector<Measurement> measurements) {
    this->log[timestamp] = measurements;
}