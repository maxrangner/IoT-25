#include <iostream>
#include <thread>
#include "UiManager.h"
#include "definitions.h"
#include "InputHandler.h"
#include "Logger.h"
#include "utils.h"

UiManager::UiManager() {
    isRunning_ = true;
}
UiManager::UiManager(SensorHub& hub, Display& disp, Logger& log) {
    isRunning_ = true;
    connectedHub = &hub;
    connectedDisplay = &disp;
    connectedLog = &log;
}

// GETTERS
bool UiManager::isRunning() const { return isRunning_; }

// STARTUP & SHUTDOWN
void UiManager::greeting() const {
    connectedDisplay->printHeader("Welcome!");
}

void UiManager::quitProcess() {
    connectedDisplay->printMessage("Bye!");
}

// CORE
void UiManager::run() {
    while(isRunning_) {
        connectedDisplay->clear();
        connectedDisplay->printMenu();
        MenuOptions choice = getMenuSelection();
        menuAction(choice); 
    }
}

MenuOptions UiManager::getMenuSelection() {
    int menuMin = static_cast<int>(MenuOptions::startOfMenu) + 1;
    int menuMax = static_cast<int>(MenuOptions::endOfmenu) - 1;
    InputIntResult menuStatus;

    do { // Loops until successful input
        menuStatus = inputHandler.getInt(menuMin, menuMax);
        if (menuStatus.status == FunctionReturnStatus::fail) {
            std::string text = "Please enter a digit between " + std::to_string(menuMin) + " and " + std::to_string(menuMax) + ".";
            connectedDisplay->printMessage(text);
            connectedDisplay->printMessage("");
        }
    } while (menuStatus.status != FunctionReturnStatus::success);

    return static_cast<MenuOptions>(menuStatus.result);
}

void UiManager::menuAction(MenuOptions choice) {
    switch (choice) { 
        case MenuOptions::addRemove: addRemoveSensors(); break; // 1.
        case MenuOptions::statusScreen: statusScreen(); break; // 2. This is a temporary function. This will bring you to a status screen with all current data displayed.
        case MenuOptions::settings: break; // 3. Not yet implemented.
        case MenuOptions::saveLoad: break; // 4. Not yet implemented.
        case MenuOptions::quit: isRunning_ = false; break; // 5.
    }
}

// ACTIONS
void UiManager::addRemoveSensors() {
    connectedDisplay->printHeader(" Add / Remove Sensors ");
    connectedDisplay->printMessage("* To add sensor: [t]emperature sensor, [h]umidity sensor.\n* To remove: enter sensor Id.\n* Press [return] to finish.");
    InputStringResult inputCommand;
    std::vector<std::string> validInputs;

    do { // Loops until successful input
        validInputs.clear();
        for (const auto& s : connectedHub->getSensorsList()) { // Creates current list of active Sensor objects.
            validInputs.emplace_back(std::to_string(s->getSensorId()));
        }
        validInputs.emplace_back("t"); // Input for [t]emperatureSensor
        validInputs.emplace_back("h"); // Input for [h]umiditySensor
        inputCommand = inputHandler.getString(validInputs);

        switch (inputCommand.status) {
            case FunctionReturnStatus::none: break;
            case FunctionReturnStatus::success: {
                if (inputCommand.result == "") break;
                if (inputCommand.result == "t"){
                    connectedHub->addSensor(SensorType::temperatureSensor);
                    connectedDisplay->printMessage("Temperature sensor added");
                    connectedDisplay->printMessage("");
                    break;
                }
                if (inputCommand.result == "h") {
                    connectedHub->addSensor(SensorType::humiditySensor);
                    connectedDisplay->printMessage("Humidity sensor added");
                    connectedDisplay->printMessage("");
                    break;
                }
                connectedHub->removeSensor(std::stoi(inputCommand.result));
                break;
            } 
            case FunctionReturnStatus::fail: {
                connectedDisplay->printMessage("Please enter a valid command.\n");
                break;
            }
        }
    } while (inputCommand.status != FunctionReturnStatus::none);
}

void UiManager::statusScreen() {
    InputStringResult inputCommand;
    std::vector<std::string> validInputs;
    int selectedSensorId = -1;
    static bool drawResult = false;
    connectedDisplay->printHeader(" StatusScreen ");

    do {
        validInputs.clear();
        validInputs.emplace_back("t");
        validInputs.emplace_back("h");
        validInputs.emplace_back("u");
        for (const auto& s : connectedHub->getSensorsList()) {
                validInputs.emplace_back(std::to_string(s->getSensorId()));
            }

        if (drawResult) {
            connectedDisplay->clear();
            connectedDisplay->printHeader(" StatusScreen ");
            connectedDisplay->printSensorsList(connectedLog->getLog(), connectedHub->getSensorsList(), connectedHub->getAlarms());
            connectedDisplay->drawGraph(connectedLog->getGraphData(selectedSensorId));
            drawResult = false;
        }

        connectedDisplay->printMessage("* Enter sensorId or \n* All sensors of type [t]emperature, [h]umidity.\n* [u]pdate.");
        inputCommand = inputHandler.getString(validInputs);

        switch (inputCommand.status) {
            case FunctionReturnStatus::none: {
                drawResult = false;
                break; 
            }
            case FunctionReturnStatus::success: {
                if (inputCommand.result == "") break;
                if (inputCommand.result == "u") {
                    if (selectedSensorId != -1) drawResult = true;
                    else connectedDisplay->printMessage("");
                    break;
                }
                if (inputCommand.result == "t") {
                    // Logic for all temperature sensors
                    drawResult = true;
                    break;
                }
                if (inputCommand.result == "h") {
                    // Logic for all humidity sensors
                    drawResult = true;
                    break;
                }
                selectedSensorId = std::stoi(inputCommand.result);
                drawResult = true;
                break;
            } 
            case FunctionReturnStatus::fail: {
                connectedDisplay->printMessage("Please enter a valid command.\n");
                drawResult = false;
                break;
            }
        }
    } while (inputCommand.status != FunctionReturnStatus::none);
}