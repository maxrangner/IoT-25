#include <iostream>
#include <string>
#include "Sensor.h"
#include "utils.h"

// STATIC VARIABLES
int Sensor::nextId = 0;

// CONSTRUCTORS
Sensor::Sensor() {}
Sensor::Sensor(int id) : sensorId(id) {}

// GETTERS
int Sensor::getNextId() {
    return nextId++;
}

void Sensor::printInfo() { // Temporary method for debug. Will be deleted.
    std::cout << "SensorId: " << sensorId << " | "
        << "SensorType: " << convertFromSensorType(sensorType) << " | "
        << "SensorUnit: " <<  sensorUnit << " | "
        << "minVal: " << minMeasure << " | "
        << "maxVal: " << maxMeasure << " | "
        << "isActive_: " << isActive_
        << std::endl;
}

int Sensor::getSensorId() const {
    return sensorId;
}

std::map<std::string, std::string> Sensor::getInfo() {
    std::map<std::string, std::string> returnVector;
    returnVector["sensorId"] = std::to_string(sensorId);
    returnVector["sensorType"] = convertFromSensorType(sensorType);
    returnVector["sensorUnit"] = sensorUnit;
    returnVector["minMeasure"] = std::to_string(minMeasure);
    returnVector["maxMeasure"] = std::to_string(maxMeasure);
    returnVector["isActive"] = std::to_string(isActive_);
    return returnVector;
}