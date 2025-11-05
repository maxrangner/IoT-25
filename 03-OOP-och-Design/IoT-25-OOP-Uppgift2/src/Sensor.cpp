#include <iostream>
#include <string>
#include "Sensor.h"
#include "utils.h"

Sensor::Sensor() {}

int Sensor::getNextId() {
    return nextId++;
}

int Sensor::nextId = 0;
int Sensor::getSensorId() const {
    return sensorId;
}
void Sensor::printInfo() {
    std::cout << "SensorId: " << sensorId << " | "
        << "SensorType: " << convertSensorType(sensorType) << " | "
        << "SensorUnit: " <<  sensorUnit << " | "
        << "minVal: " << minMeasure << " | "
        << "maxVal: " << maxMeasure << " | "
        << "isActive_: " << isActive_
        << std::endl;
}

std::map<std::string, std::string> Sensor::getInfo() {
    std::map<std::string, std::string> returnVector;
    returnVector["sensorId"] = std::to_string(sensorId);
    returnVector["sensorType"] = convertSensorType(sensorType);
    returnVector["sensorUnit"] = sensorUnit;
    returnVector["minMeasure"] = std::to_string(minMeasure);
    returnVector["maxMeasure"] = std::to_string(maxMeasure);
    returnVector["isActive"] = std::to_string(isActive_);
    return returnVector;
}