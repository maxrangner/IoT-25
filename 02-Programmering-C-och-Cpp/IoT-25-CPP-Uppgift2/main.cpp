#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <fstream>
#include "src/definitions.h"
#include "src/functions.h"
#include "src/Sensor.h"
#include "src/SystemManager.h"
#include "src/UiManager.h"

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
- Add removeSensors()
- Only collect from sensors that are ON
- Add random data generator. return simulateReading(-10.0f, 40.0f);
- Add manual sensor value entry. Only sensors that are ON
- Add Display stats
- Add history graph
- System reset option
- Clean up sensor printout
- Add error handling.

ISSUES:
- 

BUGS:
- When loading from fresh start, sensors are not added to sensorsList. Only database is filled.

*/