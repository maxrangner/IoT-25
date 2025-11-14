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

void SensorHub::readAllSensors(std::vector<int> sensors) {
    if (sensors.empty()) {
        // Logic for empty sensors list.
    }
    for (const auto& s : mySensors) {
        connectedLog->addMeasurment(s->read());
        // connectedLog->printLog();
    }
}

const std::vector<std::unique_ptr<Sensor>>& SensorHub::getSensorsList() const {
    return mySensors;
}

const Alarms& SensorHub::getAlarms() const {
    return alarms;
}

void SensorHub::setTemperatureAlarms(float low, float high) {
    alarms.temperatureLow = low;
    alarms.temperatureHigh = high;
    alarms.isOn = true;
}

void SensorHub::setHumidityAlarms(float low, float high) {
    alarms.humidityLow = low;
    alarms.humidityHigh = high;
    alarms.isOn = true;
}

void SensorHub::turnOffAlarms() {
    alarms.isOn = false;
}