#include <iostream>
#include <vector>
#include "definitions.h"
#include "functions.h"
#include "UiManager.h"

UiManager::UiManager() : isRunning(true) {}

void UiManager::addSensor(SystemManager& manager) {
    std::cout << "Add sensor: [t]emperature or [h]umidity. Leave empty to finish.\n";
    while (true) {
        std::string userInp = getInput({"t", "h", ""});
        if (userInp == "t") manager.addSensor(sensorTypes::temperatureSensor);
        if (userInp == "h") manager.addSensor(sensorTypes::humiditySensor);
        if (userInp == "") break;
    }
}

std::string UiManager::getInput(std::vector<std::string> valids) {
    std::string userInp;
    while (true) {
        userInp = getLine();
        if (userInp.empty()) return "";
        if (isValidChoice(userInp, valids)) return userInp;
        else std::cout << "Invalid input.\n";
    }
}

std::string UiManager::getInput(float min, float max) {
    std::string userInp;
    while (true) {
        userInp = getLine();
        if (userInp.empty()) return "";
        if (isValidNum(userInp, min, max)) return userInp;
        else std::cout << "Invalid input.\n";
    }
}

void UiManager::collectReadings(SystemManager& manager) {
    std::cout << "Enter deviceId or press \"enter\" for all.\n";
    std::string userInp = getInput(0, manager.getNumSensors());
    if (userInp == "") manager.collectReadings();
    else manager.collectReadings(std::stoi(userInp));
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
    std::cout << "\n*********** MENU ***********\n"
              << "1. addSensor\n"
              << "2. collectReadings\n" 
              << "3. dispData\n"
              << "4. save\n"
              << "5. load\n"
              << "6. Quit\n";

    std::string menuSelection = getInput(static_cast<float>(startofMenu + 1), static_cast<float>(endOfMenu - 1));
    menuAction(manager, std::stoi(menuSelection));
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

bool UiManager::isValidChoice(const std::string& inpStr, const std::vector<std::string>& valids) {
    for (const std::string& s : valids) {
        if (inpStr == s) return true;
    }
    return false;
}

bool UiManager::isValidNum(const std::string& inpStr, float min, float max) {
    try {
        float convertedVal = std::stof(inpStr);
        if (convertedVal >= min && convertedVal <= max) return true;
        return false;
    } catch (...) {
        return false;
    }
}