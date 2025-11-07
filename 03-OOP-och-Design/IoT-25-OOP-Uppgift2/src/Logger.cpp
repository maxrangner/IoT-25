#include <iostream>
#include "Logger.h"
#include "utils.h"

void Logger::addMeasurments(time_t timestamp, Measurement measurements) {
    std::lock_guard<std::mutex> lock(logMutex);
    this->log[timestamp].emplace_back(measurements);
}

void Logger::printLog() {
    for (const auto& [first, second] : log) {
        std::cout << readTime(first) << ":  ";
        for (const auto& m : second) {
            std::cout << "sensorId: " << m.sensorId
                    << "  |  sensorType: " << convertSensorType(m.sensorType)
                    << "  |  value: " << m.value << " " << m.sensorUnit
                    << "  |  ";
        }
        std::cout << std::endl;
    }
}