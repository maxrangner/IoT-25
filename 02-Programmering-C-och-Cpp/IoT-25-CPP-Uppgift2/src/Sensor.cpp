#include <iostream>
#include "Sensor.h"
#include "functions.h"

// CONSTRUCTORS
Sensor::Sensor() : deviceId(0), type(0), value(0.0f), isActive(true), isTriggered(false) {}
Sensor::Sensor(int id, int t) : deviceId(id), type(t), value(0.0f), isActive(true), isTriggered(false) {}
Sensor::Sensor(int id, int t, float v, bool a, bool tr)
                 : deviceId(id), type(t), value(v), isActive(a), isTriggered(tr) {}

// SIMPLE GETTERS
int Sensor::getId() { return deviceId; }
int Sensor::getType() { return type; }
DataPoint Sensor::getStatus() const {
            DataPoint newDP;
            newDP.deviceId = deviceId;
            newDP.type = type;
            newDP.value = value;
            newDP.isActive = isActive;
            newDP.isTriggered = isTriggered;
            return newDP;
        }

// FUNCTIONS
void Sensor::setValue(float val) {
    std::cout << "Sensor.setValue()";
    value = val;
}

void Sensor::updateReading() {
    switch(type) {
        case sensorTypes::temperatureSensor:
            value = getRandomNumber(18, 25);
            isTriggered = false;
            break;
        case sensorTypes::humiditySensor:
            value = getRandomNumber(40, 50);
            isTriggered = false;
            break;
    }
}

void Sensor::printInfo() {
            std::cout << "************\n"
                      << "deviceId: " << deviceId << "\n"
                      << "type: " << type << "\n"
                      << "value: " << value << "\n"
                      << "isActive: " << isActive << "\n"
                      << "isTriggered: " << isTriggered << "\n";
        }