#include <vector>
#include <ctime>
#include <map>
#include "functions.h"
#include "SystemManager.h"

SystemManager::SystemManager() : numSensors(0) {}

std::time_t SystemManager::getTime() {
    std::time_t timestamp = std::time(nullptr);
    return timestamp;
}

int SystemManager::getNumSensors() { return numSensors; }
int SystemManager::nextSensorId() { return numSensors++; }

void SystemManager::addSensor(int type) {
    sensorsList.emplace_back(nextSensorId(), type);
    numSensors = sensorsList.size();
}

void SystemManager::makeSnapshot() {
    time_t newTimestamp = getTime();
    database[newTimestamp];
    std::vector<DataPoint> data;
    for (MySensor s : sensorsList) {
        data.push_back(s.getStatus());
    }
    database[newTimestamp] = data;
}

void SystemManager::resetSystem() {
    sensorsList.clear();
    numSensors = 0;
    database.clear();
}