#include <iostream>
#include "Sensor.h"
#include <string>

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
        << "SensorType: " << sensorType << " | "
        << "SensorUnit: " <<  sensorUnit << " | "
        << "minVal: " << minMeasure << " | "
        << "maxVal: " << maxMeasure << " | "
        << "isActive: " << isActive
        << std::endl;
}