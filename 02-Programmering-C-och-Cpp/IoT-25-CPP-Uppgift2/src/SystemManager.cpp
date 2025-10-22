#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <cmath>
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
const std::vector<Sensor>& SystemManager::getSensorsList() {
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

void SystemManager::setSensorVal(int id, float val) {
    std::cout << "setSensorVal() \n";

    for (int i = 0; i < sensorsList.size(); i++) {
        if (sensorsList[i].getId() == id) {
            std::cout << "setValue() \n";
            sensorsList[i].setValue(val);
            break;
        }
    }

    std::time_t newTimestamp = getTime();
    std::vector<DataPoint> data;

    for (Sensor& s : sensorsList) {
        data.push_back(s.getStatus());
    }
    database[newTimestamp] = data;
}

Statistics SystemManager::getStatistics() {
    Statistics outputStats; 
    // if (data.empty()) return outputStats;

    outputStats.numTimeStamps = database.size();
    bool firstTemperatureRun = true;
    bool firstHumidityRun = true;

    for (const auto& pair : database) {
        std::time_t timestamp = pair.first;
        const std::vector<DataPoint>& readings = pair.second;
        for (const DataPoint& dp : readings) {
            if (dp.type == 1) {
                if (firstTemperatureRun) {
                    outputStats.minValTemperature = dp.value;
                    outputStats.maxValTemperature = dp.value;
                    firstTemperatureRun = false;
                }

                outputStats.sumTemperature += dp.value;

                if (dp.value < outputStats.minValTemperature) {
                    outputStats.minValTemperature = dp.value;
                }
                if (dp.value > outputStats.maxValTemperature) {
                    outputStats.maxValTemperature = dp.value;
                }
                outputStats.numTemperaturePoints++;
            }
            if (dp.type == 2) {
                if (firstHumidityRun) {
                    outputStats.minValHumidity = dp.value;
                    outputStats.maxValHumidity = dp.value;
                    firstHumidityRun = false;
                } 

                outputStats.sumHumidity += dp.value;

                if (dp.value < outputStats.minValHumidity) {
                    outputStats.minValHumidity = dp.value;
                }
                if (dp.value > outputStats.maxValHumidity) {
                    outputStats.maxValHumidity = dp.value;
                }
                outputStats.numHumidityPoints++;
            }
        }
    }
    if (outputStats.numTemperaturePoints) outputStats.averageTemperature = outputStats.sumTemperature / outputStats.numTemperaturePoints;
    if (outputStats.numHumidityPoints) outputStats.averageHumidity = outputStats.sumHumidity / outputStats.numHumidityPoints;

    for (const auto& pair : database) {
        std::time_t timestamp = pair.first;
        const std::vector<DataPoint>& readings = pair.second;
        for (const DataPoint& dp : readings) {
            if (dp.type == 1) {
                outputStats.varianceTemperature += (dp.value - outputStats.averageTemperature) * (dp.value - outputStats.averageTemperature);
            }
            if (dp.type == 2) {
                outputStats.varianceHumidity += (dp.value - outputStats.averageHumidity) * (dp.value - outputStats.averageHumidity);
            }
        }
    }

    outputStats.varianceTemperature = outputStats.varianceTemperature / outputStats.numTemperaturePoints;
    outputStats.varianceHumidity = outputStats.varianceHumidity / outputStats.numHumidityPoints;
    outputStats.stdDeviationTemperature = std::sqrt(outputStats.varianceTemperature);
    outputStats.stdDeviationHumidity = std::sqrt(outputStats.varianceHumidity);

    return outputStats;
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