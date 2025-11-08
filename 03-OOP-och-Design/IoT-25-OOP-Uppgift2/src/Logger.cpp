#include <iostream>
#include "Logger.h"
#include "utils.h"

Logger::Logger(Display& display) {
    connectedDisplay = &display;
}

void Logger::addMeasurments(time_t timestamp, Measurement measurements) {
    std::lock_guard<std::mutex> lock(logMutex);
    this->log[timestamp].emplace_back(measurements);
}

void Logger::printLog() {
    std::lock_guard<std::mutex> lock(logMutex);
    for (const auto& [timestamp, measurement] : log) {
        std::cout << readTime(timestamp) << ":\n";
        for (const auto& m : measurement) {
            connectedDisplay->printMessage(std::to_string(m.sensorId), false);
            connectedDisplay->printMessage("  |  ", false);
            connectedDisplay->printMessage(sensorTypeToString(m.sensorType), false);
            connectedDisplay->printMessage("  |  ", false);
            connectedDisplay->printMessage(std::to_string(m.value), false);
            connectedDisplay->printMessage(m.sensorUnit);
        }
        connectedDisplay->printMessage("\n");
    }
    connectedDisplay->printMessage("\n*************************************\n");
}