#include <iostream>
#include <sstream>
#include "Logger.h"
#include "utils.h"

Logger::Logger(Display& display) {
    connectedDisplay = &display;
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

void Logger::addMeasurment(Measurement measurement) {
    std::lock_guard<std::mutex> lock(logMutex);
    this->log.emplace_back(measurement);
    // updateGraphData(this->log);
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

bool Logger::saveData() {
    if (log.size() == 0) return false;
    std::ofstream outFile("data.csv");
    if (!outFile) return false;
    time_t lastTimestamp = log[0].timestamp;

    for (auto& Measurement : this->getLog()) {
        if (lastTimestamp != Measurement.timestamp) outFile << std::endl;

        outFile << Measurement.sensorId << ","
                << sensorTypeToString(Measurement.sensorType) << ","
                << Measurement.value << ","
                << Measurement.sensorUnit << ","
                << Measurement.timestamp << ","
                << std::endl;
        lastTimestamp = Measurement.timestamp;
    }
    outFile.close();
    
    return true;
}

bool Logger::loadData() {
    this->log.clear();
    
    std::ifstream inFile("data.csv");
    if (!inFile) return false;

    std::string newLine;

    while(std::getline(inFile, newLine)) {
        std::stringstream ss(newLine);
        std::string extractedValue;

        int fieldCount = 0;
        Measurement newMeasurement;
        
        while (std::getline(ss, extractedValue, ',')) {
            if (extractedValue.empty()) continue;
            switch (fieldCount) {
                case 0: newMeasurement.sensorId = std::stoi(extractedValue); break;
                case 1: newMeasurement.sensorType = convertToSensorType(extractedValue); break;
                case 2: newMeasurement.value = std::stof(extractedValue); break;
                case 3: newMeasurement.sensorUnit = extractedValue; break;
                case 4: newMeasurement.timestamp = std::stoll(extractedValue); break;
            }
            fieldCount++;
        }
        if (fieldCount > 0) this->log.push_back(newMeasurement);
    }

    inFile.close();
    return true;
}