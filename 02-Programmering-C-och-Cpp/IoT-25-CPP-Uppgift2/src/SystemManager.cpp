#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Sensor.h"
#include "SystemManager.h"

/******************************************************
********************* CONSTRUCTORS ********************
******************************************************/

SystemManager::SystemManager() : numSensors(0), nextSensorId(0) {}

/******************************************************
************************ TOOLS ************************
******************************************************/

std::time_t SystemManager::getTime() {

/*
time_t is used for data storage, and has to be converted to readable format when displayed.
*/

    std::time_t timestamp = std::time(nullptr);
    return timestamp;
}

/******************************************************
*********************** GETTERS ***********************
******************************************************/

int SystemManager::getNumSensors() { return numSensors; }
int SystemManager::getNextSensorId() { return nextSensorId; }
const std::vector<Sensor> SystemManager::getSensorsList() { return sensorsList; }

/******************************************************
********************* CORE METHODS ********************
******************************************************/

void SystemManager::addSensor(int type) {
    sensorsList.emplace_back(nextSensorId++, type); // Creates a sensor object directly in the vector.
    numSensors = sensorsList.size();
}

void SystemManager::removeSensor(int id) {
    for (int i = 0; i < sensorsList.size(); i++) {
        if (sensorsList[i].getId() == id) {
            sensorsList.erase(sensorsList.begin() + i);
            numSensors -= 1;
            break;
        }
    }
}

void SystemManager::collectReadings(int sensor) {
    std::time_t newTimestamp = getTime();
    std::vector<DataPoint> data;

    if (sensor < 0) { // If optional argument is left out, collect data from all Sensors. 
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

    systemStateHistory[newTimestamp] = data;
}

void SystemManager::setSensorVal(int id, float val) { // Debug feature. Not used.
    for (int i = 0; i < sensorsList.size(); i++) {
        if (sensorsList[i].getId() == id) {
            sensorsList[i].setValue(val);
            break;
        }
    }

    std::time_t newTimestamp = getTime();
    std::vector<DataPoint> data;

    for (Sensor& s : sensorsList) {
        data.push_back(s.getStatus());
    }
    systemStateHistory[newTimestamp] = data;
}

std::vector<std::vector<DataPoint>> SystemManager::sortData() {

/*
Collects all sensor readings in a multi dimentional vector, sorted by Sensor type.
*/

    std::vector<std::vector<DataPoint>> sortedData(2);

    for (auto& pair : systemStateHistory) {
        for (const DataPoint& dp : pair.second) {
            if (dp.type == sensorTypes::temperatureSensor) sortedData[0].push_back(dp);
            if (dp.type == sensorTypes::humiditySensor) sortedData[1].push_back(dp);
        }
    }
    std::sort(sortedData[0].begin(), sortedData[0].end(), [](const DataPoint& a, const DataPoint& b) {return a.value < b.value;});
    std::sort(sortedData[1].begin(), sortedData[1].end(), [](const DataPoint& a, const DataPoint& b) {return a.value < b.value;});

    return sortedData;
}

std::vector<DataPoint> SystemManager::findData(std::string searchStr) {
    std::vector<DataPoint> dataFound;
    if (isDate(searchStr)) {
        for (auto& [timestamp, DataPointVector] : systemStateHistory) {
            if (readDate(timestamp) == searchStr) {
                for (const DataPoint dp : DataPointVector) {
                    dataFound.push_back(dp);
                }
            }
        }
    } else {
        for (auto& [timestamp, DataPointVector] : systemStateHistory) {
            for (const DataPoint dp : DataPointVector) {
                if (dp.value == std::stof(searchStr)) {
                    dataFound.push_back(dp);
                }
            }
        }
    }
    // if (dataFound.empty()) {
    //     std::cout << "No data to process." << std::endl;
    // }
    return dataFound;
}

Statistics SystemManager::getStatistics() {
    Statistics outputStats; 
    // if (data.empty()) return outputStats;

    outputStats.numTimeStamps = systemStateHistory.size();
    bool firstTemperatureRun = true;
    bool firstHumidityRun = true;

    for (const auto& [timestamp, DataPointVector] : systemStateHistory) {
        for (const DataPoint& dp : DataPointVector) {
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

    for (const auto& [timestamp, DataPointVector] : systemStateHistory) {
        for (const DataPoint& dp : DataPointVector) {
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

/******************************************************
*********************** FILE I/O **********************
******************************************************/

bool SystemManager::writeToFile() {
    std::ofstream outFile("data.txt");
    if (!outFile) return false;

    for (auto& [timestamp, DataPointVector] : systemStateHistory) {
        outFile << timestamp << ",";
        for (DataPoint dp : DataPointVector) {
            outFile << dp.deviceId << ","
                    << dp.type << ","
                    << dp.value << ","
                    << dp.isActive << ","
                    << dp.isTriggered << ",";
        }
        outFile << std::endl;
    }
    outFile.close();
    return true;
}

bool SystemManager::readFromFile() {
    systemStateHistory.clear();
    
    std::ifstream inFile("data.txt");
    if (!inFile) return false;

    fileToSystemStateHistory(inFile);
    restoreSensors();

    inFile.close();
    return true;
}

void SystemManager::fileToSystemStateHistory(std::ifstream& file) {

/*
Reconstructs the DataPoints from saved systemStateHistory, and 
*/
    // systemStateHistory.clear(); // Needed?

    std::string newLine;
    while(std::getline(file, newLine)) {
        std::stringstream ss(newLine);
        std::string extractedValue;

        int loopCount = 0;
        int fieldCount = 0;

        std::time_t timestamp {};
        int id {};
        int type {};
        float value {};
        bool active {};
        bool triggered {};
        
        while (std::getline(ss, extractedValue, ',')) {
            if (extractedValue.empty()) continue;

            if (loopCount == 0) {
                timestamp = stoll(extractedValue);
                loopCount++;
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
                    systemStateHistory[timestamp].emplace_back(id, type, value, active, triggered);
                }
                fieldCount = 0;
            }
            loopCount++;
        }
    }
}

/******************************************************
************************ OTHER ************************
******************************************************/

void SystemManager::restoreSensors() {

/*
Restore the Sensors from the last snapshot in systemStateHistory.
*/

    std::vector<DataPoint> lastMeasure;
    std::vector<Sensor> newSensorsList;
    int newNextSensorId = 0;

    for (const auto& [timestamp, DataPointVector] : systemStateHistory) {
        lastMeasure = DataPointVector;
    }
    for (const DataPoint& dp : lastMeasure) {
        newSensorsList.emplace_back(dp.deviceId, dp.type);
        if (newNextSensorId < dp.deviceId + 1) newNextSensorId = dp.deviceId + 1;
    }
    sensorsList = newSensorsList;
    nextSensorId = newNextSensorId;
    numSensors = sensorsList.size();
}

void SystemManager::resetSystem() {
    sensorsList.clear();
    numSensors = 0;
    systemStateHistory.clear();
}
