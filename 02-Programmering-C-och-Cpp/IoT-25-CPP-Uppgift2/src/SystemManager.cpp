#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <fstream>
#include <sstream>
#include "Sensor.h"
#include "SystemManager.h"

// CONSTRUCTORS
SystemManager::SystemManager() : numSensors(0) {}

// TOOLS
std::time_t SystemManager::getTime() {
    std::time_t timestamp = std::time(nullptr);
    return timestamp;
}

// SIMPLE GETTERS
int SystemManager::getNumSensors() { return numSensors; }
int SystemManager::nextSensorId() { return numSensors++; }
const std::vector<Sensor> SystemManager::getSensorsList() {
    return sensorsList;
}

// FUNCTIONS
void SystemManager::addSensor(int type) {
    sensorsList.emplace_back(nextSensorId(), type);
    numSensors = sensorsList.size();
}

void SystemManager::removeSensor(int id) {
    for (int i = 0; i < sensorsList.size(); i++) {
        if (sensorsList[i].getId() == id) {
            sensorsList.erase(sensorsList.begin() + i);
            break;
        }
    }
}

void SystemManager::collectReadings(int sensor) {
    std::time_t newTimestamp = getTime();
    std::vector<DataPoint> data;

    if (sensor < 0) {
        for (Sensor& s : sensorsList) {
            if (s.getStatus().isActive) {
                s.updateReading();
                data.push_back(s.getStatus());
            }
        }
    } else {
        sensorsList[sensor].updateReading();
        data.push_back(sensorsList[sensor].getStatus());
    }

    database[newTimestamp] = data;
}

bool SystemManager::writeToFile() {
    std::cout << "WRITE!";
    std::ofstream outFile("data.txt");
    if (!outFile) return false;

    for (auto& pair : database) {
        outFile << pair.first << ",";
        for (DataPoint DP : pair.second) {
            outFile << DP.deviceId << ","
                    << DP.type << ","
                    << DP.value << ","
                    << DP.isActive << ","
                    << DP.isTriggered << ",";
        }
        outFile << std::endl;
    }
    outFile.close();
    return true;
}

bool SystemManager::readFromFile() {
    database.clear();
    
    std::ifstream inFile("data.txt");
    if (!inFile) return false;

    std::string newLine;
    while(std::getline(inFile, newLine)) {
        std::stringstream ss(newLine);
        std::string extractedValue;

        int indexCount {};
        int fieldCount {};

        std::time_t timestamp {};
        int id {};
        int type {};
        float value {};
        bool active {};
        bool triggered {};
        
        while (std::getline(ss, extractedValue, ',')) {
            if (extractedValue.empty()) continue;

            if (indexCount == 0) {      // första värdet
                timestamp = stoll(extractedValue);
                indexCount++;
                continue;
            }

            switch (fieldCount) {
                case 0: id = std::stoi(extractedValue); break;
                case 1: type = std::stoi(extractedValue); break;
                case 2: value = std::stof(extractedValue); break;
                case 3: active = std::stoi(extractedValue) ? true : false; break;
                case 4: triggered = std::stoi(extractedValue) ? true : false; break;
            }
            fieldCount++;
            if (fieldCount == 5) {
                if (!extractedValue.empty()) {
                    database[timestamp].emplace_back(id, type, value, active, triggered);
                }
                fieldCount = 0;
            }
            indexCount++;
        }
    }
    // manager.loadSensors();
    inFile.close();
    return true;
}

void SystemManager::resetSystem() {
    sensorsList.clear();
    numSensors = 0;
    database.clear();
}