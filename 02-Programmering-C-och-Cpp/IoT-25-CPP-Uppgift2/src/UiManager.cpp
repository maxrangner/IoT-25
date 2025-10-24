#include <iostream>
#include <vector>
#include <iomanip>
#include "definitions.h"
#include "functions.h"
#include "UiManager.h"

UiManager::UiManager() : isRunning(true) {}

/******************************************************
********************* START / QUIT ********************
******************************************************/

void UiManager::greeting() {
    std::cout << "***************************************\n"
              << "********** SUPER SENSOR HUB ***********\n"
              << "***************************************\n" << std::endl;
}

void UiManager::exitPrompt() {
    std::cout << "\n\n********** THANKS! **********\n\n" << std::endl;
}

/******************************************************
************************* MENU ************************
******************************************************/

void UiManager::menu(SystemManager& manager) {
    int spacing = 4;

    std::cout << "\n*--- MENU ---*\n"
              << std::left << std::setw(spacing) << "1." << "Add Sensor\n"
              << std::left << std::setw(spacing) << "2." << "Remove Sensor\n"
              << std::left << std::setw(spacing) << "3." << "Collect Readings\n"
              << std::left << std::setw(spacing) << "4." << "Display Collected Readings\n"
              << std::left << std::setw(spacing) << "5." << "Sort Collected Readings\n"
              << std::left << std::setw(spacing) << "6." << "Find Collected Readings\n"
              << std::left << std::setw(spacing) << "7." << "Disp Statistics from Collected Readings\n"
              << std::left << std::setw(spacing) << "8." << "Save System State\n"
              << std::left << std::setw(spacing) << "9." << "Load System State\n"
              << std::left << std::setw(spacing) << "10." << "Quit\n"
              << "*-----------*" << std::endl;

    std::string menuSelection = getInput(MenuSelection::startofMenu + 1, MenuSelection::endOfMenu - 1, false);
    menuAction(manager, std::stoi(menuSelection)); // getInput() always returns a string.
}

void UiManager::menuAction(SystemManager& manager, int chosenAction) {
    switch (chosenAction) { 
        case MenuSelection::addSensor: addSensor(manager); break;
        case MenuSelection::removeSensor: removeSensor(manager); break;
        case MenuSelection::collectReadings: collectReadings(manager); break;
        case MenuSelection::dispData: displayData(manager); break;
        case MenuSelection::sortData: sortData(manager); break;
        case MenuSelection::findData: findData(manager); break;
        case MenuSelection::dispStats: displayStats(manager); break;
        case MenuSelection::save: saveSystemState(manager); break;
        case MenuSelection::load: loadSystemState(manager); break;
        case MenuSelection::quit: exitPrompt(); isRunning = false;
    }
}

/******************************************************
************************ INPUT  ***********************
******************************************************/

/*
All getInput returns a string cleared by the different validators.
allowNonReturn = true allows the user to press "enter" without a value to cancel.
*/

std::string UiManager::getInput(const std::vector<std::string>& valids, bool allowNonReturn) {
    std::string userInp;
    while (true) {
        userInp = getLine();
        if (userInp.empty() && allowNonReturn) return ""; 
        if (isValidChoice(userInp, valids)) return userInp;
        else std::cout << "Invalid input.\n";
    }
}

std::string UiManager::getInput(float min, float max, bool allowNonReturn) {
    std::string userInp;
    while (true) {
        userInp = getLine();
        if (userInp.empty() && allowNonReturn) return "";
        if (isValidNum(userInp, min, max)) return userInp;
        else std::cout << "Invalid input.\n";
    }
}

std::string UiManager::getInput(bool allowNonReturn) {
    std::string userInp;
    while (true) {
        userInp = getLine();
        if (userInp.empty() && allowNonReturn) return "";
        if (isDate(userInp)) return userInp;
        if (isValidNum(userInp)) return userInp;
        else std::cout << "Invalid input.\n";
    }
}

/******************************************************
********************* CORE METHODS ********************
******************************************************/

void UiManager::addSensor(SystemManager& manager) {

/*
Adds sensors until user cancels by pressing "enter" with no value.
Different sensors can be added by including a new if-statement.
*/

    int addCount = 0;
    std::cout << "Add sensor: [t]emperature or [h]umidity. Leave empty to finish.\n";

    while (true) {
        std::string userInp = getInput({"t", "h", ""});
        if (userInp == "") break;
        if (userInp == "t") manager.addSensor(sensorTypes::temperatureSensor);
        if (userInp == "h") manager.addSensor(sensorTypes::humiditySensor);
        addCount++;
    }

    std::cout << addCount << " sensors added.\n";
}

void UiManager::removeSensor(SystemManager& manager) {
    if (manager.getSensorsList().size() <= 0) {
        std::cout << "No sensors registered." << std::endl;
        return;
    }

    std::cout << "Enter Id for sensor to be removed. Leave empty to finish.\n";

    while (true) {
        std::vector<std::string> validIds;
        for (Sensor s : manager.getSensorsList()) { // Creates a list of current Sensor deviceIds.
            std::string newId = std::to_string(s.getId()); 
            validIds.push_back(newId);
        }
        std::string userInp = getInput(validIds);
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
    std::string userInp = getInput(0, manager.getNumSensors()); // Unsafe. Does not guard against deleted sensors. Give list of current sensorIds instead.

    if (userInp == "") manager.collectReadings();
    else manager.collectReadings(std::stoi(userInp));
}

void UiManager::setSensorValue(SystemManager& manager) {
    if (manager.getNumSensors() <= 0) {
        std::cout << "No sensors registered." << std::endl;
        return;
    }

    std::cout << "Enter sensorId: \n";
    int userInp = std::stoi(getInput(0, manager.getNumSensors() - 1)); // Unsafe. Does not guard against deleted sensors. Give list of current sensorIds instead.

    std::cout << "Enter value: \n";
    int newVal = std::stoi(getInput(DEFAULT_MIN_INPUT,DEFAULT_MAX_INPUT));

    manager.setSensorVal(userInp, newVal);        
}

void UiManager::displayData(SystemManager& manager) {
        for (auto& [timestamp, SensorsVector] : manager.systemStateHistory) {
            std::cout << "\n*---------------- " << readTime(timestamp) << " ----------------*\n";
            for (DataPoint& dp : SensorsVector) {
                std::cout << std::fixed << std::setprecision(2)
                          << "deviceId: " << dp.deviceId << " | "
                          << "type: " << convertSensorType(dp.type) << ((dp.type == 1) ? "" : "   ") << " | "
                          << "value: " << dp.value << " " << dp.getUnit() << " | "
                          << "isActive: " << ((dp.isActive) ? "true" : "false") << " | "
                          << "isTriggered: " << ((dp.isTriggered) ? "true" : "false") << "\n";
            }
            std::cout << std::endl;;
        }
}

void UiManager::displayStats(SystemManager& manager) {
    Statistics newStats = manager.getStatistics();
    int spacing = 30;

    std::cout << std::left << std::setw(spacing) << "*---------------- TEMPERATURE ----------------*" << std::endl
              << std::left << std::setw(spacing) << "Sum: " << newStats.sumTemperature << std::endl
              << std::left << std::setw(spacing) << "Average:" << newStats.averageTemperature << std::endl
              << std::left << std::setw(spacing) << "Min:" << newStats.minValTemperature << std::endl
              << std::left << std::setw(spacing) << "Max:" << newStats.maxValTemperature << std::endl
              << std::left << std::setw(spacing) << "Variance:" << newStats.varianceTemperature << std::endl
              << std::left << std::setw(spacing) << "Standard deviation:" << newStats.stdDeviationTemperature << std::endl
              << std::left << std::setw(spacing) << "\n*---------------- HUMIDITY ----------------*" << std::endl
              << std::left << std::setw(spacing) << "Sum: " << newStats.sumHumidity << std::endl
              << std::left << std::setw(spacing) << "Average:" << newStats.averageHumidity << std::endl
              << std::left << std::setw(spacing) << "Min:" << newStats.minValHumidity << std::endl
              << std::left << std::setw(spacing) << "Max:" << newStats.maxValHumidity << std::endl
              << std::left << std::setw(spacing) << "Variance:" << newStats.varianceHumidity << std::endl
              << std::left << std::setw(spacing) << "Standard deviation:" << newStats.stdDeviationHumidity << std::endl;
}

void UiManager::sortData(SystemManager& manager) {
    if (manager.systemStateHistory.empty()) {
        std::cout << "No data to process." << std::endl;
        return;
    }

    int index {};
    for (const std::vector vec : manager.sortData()) {
        if (index == 0) std::cout << "*--------------- TEMPERATURE --------------*" << std::endl;
        if (index == 1) std::cout << "*---------------- HUMIDITY ----------------*" << std::endl;
        for (const DataPoint dp : vec) {
            std::cout << "deviceId: " << dp.deviceId << " | "
                      << "type: " << convertSensorType(dp.type) << ((dp.type == 1) ? "" : "   ") << " | "
                      << "value: " << dp.value << " | "
                      << "isActive: " << ((dp.isActive) ? "true" : "false") << " | "
                      << "isTriggered: " << ((dp.isTriggered) ? "true" : "false") << "\n";
        }
        std::cout << std::endl;
        index++;
    }
}

void UiManager::findData(SystemManager& manager) {
    std::cout << "Find data: enter date (xxxx/xx/xx) or value.\n";

    while (true) {
        std::string userInp = getInput();
        if (userInp.empty()) break;
        if (isValidNum(userInp)) {
            for (auto& v : manager.findData(userInp)) {
                    std::cout << "deviceId: " << v.deviceId << " | "
                            << "type: " << convertSensorType(v.type) << ((v.type == 1) ? "" : "   ") << " | "
                            << "value: " << v.value << " | "
                            << "isActive: " << ((v.isActive) ? "true" : "false") << " | "
                            << "isTriggered: " << ((v.isTriggered) ? "true" : "false") << "\n";
                }
            std::cout << std::endl;;
            return;
        }
    }
}

/******************************************************
*********************** FILE I/O **********************
******************************************************/

void UiManager::saveSystemState(SystemManager& manager) {
    manager.writeToFile();
    std::cout << "\n***************************************\n"
              << "********* SYSTEM STATE SAVED **********\n"
              << "***************************************\n" << std::endl;
}

void UiManager::loadSystemState(SystemManager& manager) {
    manager.readFromFile();
        std::cout << "\n***************************************\n"
                  << "********* SYSTEM STATE LOADED *********\n"
                  << "***************************************\n" << std::endl;
}
