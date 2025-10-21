#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <ctime>
#include <fstream>
#include "src/definitions.h"
#include "src/functions.h"
#include "src/Sensor.h"
#include "src/SystemManager.h"

int main() {
    SystemManager manager;

    manager.addSensor(temperatureSensor);
    manager.addSensor(humiditySensor);

    manager.makeSnapshot();
    std::cin.get();
    manager.addSensor(temperatureSensor);
    manager.makeSnapshot();

    printDatabase(manager.database);

    if (writeToFile(manager.database)) std::cout << "Database saved!\n";
    else std::cout << "Error saving database!\n";

    if (readFromFile(manager.database)) std::cout << "Database loaded.\n";
    else std::cout << "Error loading database!\n";

    printDatabase(manager.database);
}

/*
ISSUES:
- 

BUGS:
- 
*/