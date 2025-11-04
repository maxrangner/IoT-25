#include <memory>
#include <iostream>
#include <string>
#include "SensorHub.h"
#include "Sensor.h"

void SensorHub::addSensor() {
    mySensors.emplace_back(std::make_unique<TemperatureSensor>());
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