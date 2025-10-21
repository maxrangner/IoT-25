#include <iostream>
#include "definitions.h"
#include "Sensor.h"

MySensor::MySensor() : deviceId(0), type(0), value(0.0f), isActive(true), isTriggered(false) {}
MySensor::MySensor(int id, int t) : deviceId(id), type(t) {
    value = 0.0f;
    isActive = true;
    isTriggered = false;
}
MySensor::MySensor(int id, int t, float v, bool a, bool tr)
                 : deviceId(id), type(t), value(v), isActive(a), isTriggered(tr) {}
        
int MySensor::getId() { return deviceId; }
int MySensor::getType() { return type; }
DataPoint MySensor::getStatus() {
            DataPoint newDP;
            newDP.deviceId = deviceId;
            newDP.type = type;
            newDP.value = value;
            newDP.isActive = isActive;
            newDP.isTriggered = isTriggered;
            return newDP;
        }

void MySensor::setVal(float newVal) { value = newVal; }
void MySensor::printInfo() {
            std::cout << "************\n"
                      << "deviceId: " << deviceId << "\n"
                      << "type: " << type << "\n"
                      << "value: " << value << "\n"
                      << "isActive: " << isActive << "\n"
                      << "isTriggered: " << isTriggered << "\n";
        }