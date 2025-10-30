#include "SensorHub.h"

    void SensorHub::addSensor() {
        Sensor* newSensor = new TemperatureSensor;
        mySensors.push_back(newSensor);
    }
    void SensorHub::removeSensor(int id) {
        for (int i = 0; i < mySensors.size(); i++) {
            if (mySensors[i]->getSensorId() == id) {
                mySensors.erase(mySensors.begin() + i);
            }
        }
    }

    void SensorHub::printAllInfo() {
        for (Sensor* const s : mySensors) {
            s->printInfo();
        }
    }