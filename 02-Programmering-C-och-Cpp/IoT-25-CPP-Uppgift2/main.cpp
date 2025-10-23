#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <fstream>
#include "definitions.h"
#include "functions.h"
#include "Sensor.h"
#include "SystemManager.h"
#include "UiManager.h"

int main() {
    SystemManager manager;
    UiManager Ui;

    while (Ui.isRunning) {
        Ui.menu(manager);
    }
    std::cout << "Bye!\n";
    return 0;
}

/*
TO DO:
- Check to add const&
- Add toggle sensor on / off
- Add error handling.
- Add history graph
- System reset option
- Make sensors list a map with <id, sensor>
- Make database struxt instead of map
- Search by day, month, or year.

WANT TO DO
- Make better input validation.

ISSUES:
- 

BUGS:
- When loading from fresh start, sensors are not added to sensorsList. Only database is filled.
- Print out of database shows 20.0. Fix always show two decimals.

*/