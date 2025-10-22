#include <iostream>
#include <vector>
#include <cfloat>
#include "definitions.h"
#include "UiManager.h"

UiManager::UiManager() : isRunning(true) {}

void UiManager::addSensor(SystemManager& manager) {
    std::string userInp;
    std::cout << "Add sensor: [t]emperature or [h]umidity.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, userInp);
        if (isValidChoice(userInp, {"t", "h"})) {
            if (userInp == "t") manager.addSensor(temperatureSensor);
            else manager.addSensor(humiditySensor);
            break;
        } else std::cout << "Invalid input.\n";
    }
}

void UiManager::collectReadings(SystemManager& manager) {
    manager.collectReadings();
}

void UiManager::displayData(SystemManager& manager) {
        for (auto& pair : manager.database) {
        std::cout << "Timestamp: " << pair.first << ":\n";
        for (auto& v : pair.second) {
            std::cout << "**************\n"
                      << "deviceId: " << v.deviceId << " | "
                      << "type: " << v.type << " | "
                      << "value: " << v.value << " | "
                      << "isActive: " << v.isActive << " | "
                      << "isTriggered: " << v.isTriggered << "\n";
        }
        std::cout << std::endl;
    }
}

void UiManager::saveData(SystemManager& manager) {
    manager.writeToFile();
}

void UiManager::loadData(SystemManager& manager) {
    manager.readFromFile();
}

void UiManager::menu(SystemManager& manager) {
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
            menuAction(manager, menuChoice);
            return;
        }
    }
}

bool UiManager::menuAction(SystemManager& manager, int chosenAction) {
    switch (chosenAction) { 
        case MenuSelection::addSensor: addSensor(manager); break;
        case MenuSelection::collectReadings: collectReadings(manager); break;
        case MenuSelection::dispData: displayData(manager); break;
        case MenuSelection::save: saveData(manager); break; // writeToFile(manager.database); Change to manager
        case MenuSelection::load: loadData(manager); break; // readFromFile(manager);
        case MenuSelection::quit: return true;
    }
    return false;
}

// bool UiManager::isValidNum(std::string inpStr, float min, float max) {

// }

bool UiManager::isValidChoice(const std::string& inpStr, const std::vector<std::string>& valids) {
    for (const std::string& s : valids) {
        if (inpStr == s) return true;
    }
    return false;
}