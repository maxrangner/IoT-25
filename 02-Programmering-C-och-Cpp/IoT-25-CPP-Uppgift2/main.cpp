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
    Ui.greeting();

    while (Ui.isRunning) {
        Ui.menu(manager);
    }
    return 0;
}
