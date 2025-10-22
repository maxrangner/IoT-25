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
  PRIO:
- Add manual sensor value entry
- Add Display stats
- Add sort DataPoint
- Add find DataPoint

  BONUS:
- Restore sensors at file load
- Add toggle sensor on / off
- Add history graph
- System reset option
- Clean up sensor printout
- Add error handling.

ISSUES:
- 

BUGS:
- When loading from fresh start, sensors are not added to sensorsList. Only database is filled.

*/