#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <ctime>
#include <fstream>
#include "src/definitions.h"
#include "src/Sensor.h"
#include "src/SystemManager.h"

int main() {
    SystemManager manager;

    manager.addSensor(temperatureSensor);
    manager.addSensor(humiditySensor);

    manager.makeSnapshot();
    std::cin.get();
    manager.makeSnapshot();

    for (auto& pair : manager.database) {
        std::cout << "Timestamp: " << pair.first << ":\n";
        for (auto& v : pair.second) {
            std::cout << "**************\n"
                      << "deviceId: " << v.deviceId << "\n"
                      << "type: " << v.type << "\n"
                      << "value: " << v.value << "\n"
                      << "isActive: " << v.isActive << "\n"
                      << "isTriggered: " << v.isTriggered << "\n";
        }
        std::cout << std::endl;
    }
}

/*
ISSUES:
- 

BUGS:
- 
*/