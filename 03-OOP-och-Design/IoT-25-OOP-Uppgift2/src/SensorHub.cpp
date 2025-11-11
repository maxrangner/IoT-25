#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include "SensorHub.h"
#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "Logger.h"
#include "utils.h"

SensorHub::SensorHub(Logger& log) {
    connectedLog = &log;
    updateInterval = 2; // Seconds
}

int SensorHub::getUpdateInterval() const {
    return updateInterval;
}

void SensorHub::addSensor(SensorType type) {
    switch (type) {
        case SensorType::temperatureSensor: mySensors.emplace_back(std::make_unique<TemperatureSensor>()); break;
        case SensorType::humiditySensor: mySensors.emplace_back(std::make_unique<HumiditySensor>()); break;
        case SensorType::motionSensor: break;
        case SensorType::waterSensor: break;
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
        connectedLog->addMeasurments(now, s->read());
    }
}

void SensorHub::printAllInfo() const {
    for (const std::unique_ptr<Sensor>& s : mySensors) {
        s->printInfo();
    }
}

const std::vector<std::unique_ptr<Sensor>>& SensorHub::getSensorsList() const {
    return mySensors;
}

void SensorHub::printCurrentData() {
    std::vector<Measurement> currentData = connectedLog->getLatestEntry();
    for (auto& m : currentData) {
        std::cout << "id: " << m.sensorId << " | "
                << "type: " << sensorTypeToString(m.sensorType) << " | "
                << m.value << " " << m.sensorUnit
                << std::endl;
    }
}