#include <memory>
#include <iostream>
#include <string>
#include "SensorHub.h"
#include "TemperatureSensor.h"
#include "HumiditySensor.h"

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

void SensorHub::printAllInfo() {
    for (std::unique_ptr<Sensor>& s : mySensors) {
        s->printInfo();
    }
}

const std::vector<std::unique_ptr<Sensor>>& SensorHub::getSensorsList() const {
    return mySensors;
}