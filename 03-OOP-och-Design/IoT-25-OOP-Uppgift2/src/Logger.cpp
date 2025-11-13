#include <iostream>
#include "Logger.h"
#include "utils.h"

Logger::Logger(Display& display) {
    connectedDisplay = &display;
}

void Logger::addMeasurment(Measurement measurement) {
    std::lock_guard<std::mutex> lock(logMutex);
    this->log.emplace_back(measurement);
    // updateGraphData(this->log);
}

void Logger::printLog() {
    std::lock_guard<std::mutex> lock(logMutex);
    for (const auto& m : log) {
        connectedDisplay->printMessage(std::to_string(m.timestamp), false);
        connectedDisplay->printMessage("  |  ", false);
        connectedDisplay->printMessage(std::to_string(m.sensorId), false);
        connectedDisplay->printMessage("  |  ", false);
        connectedDisplay->printMessage(sensorTypeToString(m.sensorType), false);
        connectedDisplay->printMessage("  |  ", false);
        connectedDisplay->printMessage(std::to_string(m.value), false);
        connectedDisplay->printMessage(m.sensorUnit);
    }
    connectedDisplay->printMessage("\n");
    connectedDisplay->printMessage("\n*************************************\n");
}

std::vector<Measurement>& Logger::getLog() {
    return log;
}

std::array<Measurement, 10> Logger::getGraphData(int sensorId) {
    std::array<Measurement, 10> newGraphData = {};
    int index = 9;
    for (auto it = log.rbegin(); it != log.rend(); it++) {
        Measurement m = *it;
        if (m.sensorId == sensorId) {
            newGraphData[index--] = m;
        }
        if (index < 0) break;
    }
    return newGraphData;
}