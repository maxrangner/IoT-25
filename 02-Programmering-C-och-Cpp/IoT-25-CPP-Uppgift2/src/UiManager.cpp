#include <iostream>
#include <vector>
#include <iomanip>
#include "definitions.h"
#include "functions.h"
#include "UiManager.h"

UiManager::UiManager() : isRunning(true) {}

std::string UiManager::getInput(const std::vector<std::string>& valids) {
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

void UiManager::addSensor(SystemManager& manager) {
    std::cout << "Add sensor: [t]emperature or [h]umidity. Leave empty to finish.\n";

    while (true) {
        std::string userInp = getInput({"t", "h", ""});
        if (userInp == "") break;
        if (userInp == "t") manager.addSensor(sensorTypes::temperatureSensor);
        if (userInp == "h") manager.addSensor(sensorTypes::humiditySensor);
    }
}

void UiManager::removeSensor(SystemManager& manager) {
    std::cout << "Enter Id for sensor to be removed. Leave empty to finish.\n";

    while (true) {
        std::string userInp = getInput(0, manager.getSensorsList().size());
        if (userInp.empty()) break;
        manager.removeSensor(std::stoi(userInp));
    }
}

void UiManager::collectReadings(SystemManager& manager) {
    if (manager.getNumSensors() <= 0) {
        std::cout << "No sensors registered." << std::endl;
        return;
    }

    std::cout << "Enter deviceId or press \"enter\" for all.\n";

    std::string userInp = getInput(0, manager.getNumSensors());
    if (userInp == "") manager.collectReadings();
    else manager.collectReadings(std::stoi(userInp));
}

void UiManager::setSensorValue(SystemManager& manager) {
    if (manager.getNumSensors() <= 0) {
        std::cout << "No sensors registered." << std::endl;
        return;
    }

    std::cout << "Enter sensorId: \n";

    int userInp = std::stoi(getInput(0, manager.getNumSensors() - 1));
    std::cout << "Enter value: \n";

    int newVal = std::stoi(getInput());
    manager.setSensorVal(userInp, newVal);        
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

void UiManager::displayStats(SystemManager& manager) {
    Statistics newStats = manager.getStatistics();
    int spacing = 30;

    std::cout << std::left << std::setw(spacing) << "*** TEMPERATURE ***" << std::endl
              << std::left << std::setw(spacing) << "Sum: " << newStats.sumTemperature << std::endl
              << std::left << std::setw(spacing) << "Average:" << newStats.averageTemperature << std::endl
              << std::left << std::setw(spacing) << "Min:" << newStats.minValTemperature << std::endl
              << std::left << std::setw(spacing) << "Max:" << newStats.maxValTemperature << std::endl
              << std::left << std::setw(spacing) << "Variance:" << newStats.varianceTemperature << std::endl
              << std::left << std::setw(spacing) << "Standard deviation:" << newStats.stdDeviationTemperature << std::endl
              << std::left << std::setw(spacing) << "\n*** HUMIDITY ***" << std::endl
              << std::left << std::setw(spacing) << "Sum: " << newStats.sumHumidity << std::endl
              << std::left << std::setw(spacing) << "Average:" << newStats.averageHumidity << std::endl
              << std::left << std::setw(spacing) << "Min:" << newStats.minValHumidity << std::endl
              << std::left << std::setw(spacing) << "Max:" << newStats.maxValHumidity << std::endl
              << std::left << std::setw(spacing) << "Variance:" << newStats.varianceHumidity << std::endl
              << std::left << std::setw(spacing) << "Standard deviation:" << newStats.stdDeviationHumidity << std::endl;
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
              << "2. removeSensor\n"
              << "3. collectReadings\n"
              << "4. setSensorValue\n" 
              << "5. dispData\n"
              << "6. dispStats\n"
              << "7. save\n"
              << "8. load\n"
              << "9. Quit\n";

    std::string menuSelection = getInput(static_cast<float>(startofMenu + 1), static_cast<float>(endOfMenu - 1));
    menuAction(manager, std::stoi(menuSelection));
}

bool UiManager::menuAction(SystemManager& manager, int chosenAction) {
    switch (chosenAction) { 
        case MenuSelection::addSensor: addSensor(manager); break;
        case MenuSelection::removeSensor: removeSensor(manager); break;
        case MenuSelection::collectReadings: collectReadings(manager); break;
        case MenuSelection::setSensorValue: setSensorValue(manager); break;
        case MenuSelection::dispData: displayData(manager); break;
        case MenuSelection::dispStats: displayStats(manager); break;
        case MenuSelection::save: saveData(manager); break;
        case MenuSelection::load: loadData(manager); break;
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