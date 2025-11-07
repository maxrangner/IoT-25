#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include "SensorHub.h"
#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "utils.h"

SensorHub::SensorHub(Logger& log) {
    connectedLog = &log;
    updateInterval = 10; // Seconds
}

int SensorHub::getUpdateInterval() const {
    return updateInterval;
}

void SensorHub::addSensor(SensorType type) {
    switch (type) {
        case SensorType::temperatureSensor: mySensors.emplace_back(std::make_unique<TemperatureSensor>()); break;
        case SensorType::humiditySensor: mySensors.emplace_back(std::make_unique<HumiditySensor>()); break;
    }
}

void SensorHub::removeSensor(int id) {
    for (int i = 0; i < mySensors.size(); i++) {
        if (mySensors[i]->getSensorId() == id) {
            mySensors.erase(mySensors.begin() + i);
        }
    }
}

void SensorHub::updateSensors(std::vector<int> sensors) {
    time_t now = getTime();
    if (sensors.empty()) {
        // Logic for empty sensors list.
    }
    for (const auto& s : mySensors) {

    }
}

void SensorHub::printAllInfo() {
    for (std::unique_ptr<Sensor>& s : mySensors) {
        s->printInfo();
    }
}

const std::vector<std::unique_ptr<Sensor>>& SensorHub::getSensorsList() const {
    return mySensors;
}

void SensorHub::readAllSensors() {
    time_t timestamp = getTime();
    for (auto& s : mySensors) {
        connectedLog->addMeasurments(timestamp, s->read());
    }
}