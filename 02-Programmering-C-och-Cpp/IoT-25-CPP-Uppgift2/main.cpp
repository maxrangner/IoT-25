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

int menu() {
    int menuChoice = 0;
    std::string input;

    std::cout << "\n*********** MENU ***********\n"
              << "1. addSensor\n"
              << "2. collectReadings\n"
              << "3. dispData\n"
              << "4. save\n"
              << "5. load\n"
              << "6. Quit\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (isValidInput(input, wholeNum, startofMenu + 1, endOfMenu - 1)) {
            menuChoice = std::stoi(input);
            return menuChoice;
        }
    }
}

bool action(int chosenAction, SystemManager& manager) {
    switch (chosenAction) { 
        case addSensor: manager.addSensor(temperatureSensor); break;
        case collectReadings: manager.makeSnapshot(); break;
        case dispData: printDatabase(manager.database); break;
        case save: writeToFile(manager.database); break;
        case load: readFromFile(manager.database); break;
        case quit: return true;
    }
    return false;
}

int main() {
    SystemManager manager;
    std::vector<DataPoint> temperatureData;
    bool shouldQuit = false;

    while (!shouldQuit) {
        int choice = menu();
        shouldQuit = action(choice, manager);
    }
    std::cout << "Bye!\n";
    return 0;
}

/*
ISSUES:
- 

BUGS:
- When saving data, the loading, then manually deleteing data from data.txt, then collectReadings - the old sensor are ghosts and register new data. 

*/