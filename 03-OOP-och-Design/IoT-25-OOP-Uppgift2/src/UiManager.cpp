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
        case MenuOptions::settings: setAlarms(); break; // 3. Not yet implemented.
        case MenuOptions::saveLoad: break; // 4. Not yet implemented.
        case MenuOptions::quit: isRunning_ = false; break; // 5.
    }
}

// ACTIONS
void UiManager::addRemoveSensors() {
    connectedDisplay->printHeader(" Add / Remove Sensors ");
    connectedDisplay->printMessage("> To add sensor: [t]emperature sensor, [h]umidity sensor.\n> To remove: enter sensor Id.\n> Press [return] to finish.");
    InputStringResult inputCommand;
    std::vector<std::string> validInputs;

    do { // Loops until successful input
        validInputs = buildValidInputs({"t", "h"});
        inputCommand = inputHandler.getString(validInputs);

        switch (inputCommand.status) {
            case FunctionReturnStatus::none: break;
            case FunctionReturnStatus::success: {
                if (inputCommand.result == "") break;
                if (inputCommand.result == "t"){
                    connectedHub->addSensor(SensorType::temperatureSensor);
                    connectedDisplay->printMessage("Temperature sensor added");
                    break;
                }
                if (inputCommand.result == "h") {
                    connectedHub->addSensor(SensorType::humiditySensor);
                    connectedDisplay->printMessage("Humidity sensor added");
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
        validInputs = buildValidInputs({"u"});
        if (drawResult) {
            // DRAW GRAPH SCREEN
            connectedDisplay->clear();
            connectedDisplay->printHeader(" StatusScreen ");
            connectedDisplay->printSensorsList(connectedLog->getLog(), connectedHub->getSensorsList(), connectedHub->getAlarms());
            connectedDisplay->drawGraph(connectedLog->getGraphData(selectedSensorId));
            connectedDisplay->printStats(connectedLog->getLog());
            drawResult = false;
        }

        connectedDisplay->printMessage("> [num] sensorId.\n> [u]pdate.\n> [enter] to go back.");
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

void UiManager::setAlarms() {
    connectedDisplay->printHeader(" Set Alarms ");
    connectedDisplay->printMessage("> [t]emperature sensor\n> [h]umidity sensor\n> Press [return] to finish.");
    InputStringResult inputCommand;
    std::vector<std::string> validInputs;

    do { // Loops until successful input
        validInputs = buildValidInputs({"t", "h"});
        inputCommand = inputHandler.getString(validInputs);

        switch (inputCommand.status) {
            case FunctionReturnStatus::none: break;
            case FunctionReturnStatus::success: {
                if (inputCommand.result == "") break;
                if (inputCommand.result == "t"){
                    connectedDisplay->printMessage("> Enter [low] then [high]\n> Enter [return] or [0] to turn alarms off.");
                    
                    InputIntResult tempMin;
                    do {
                        tempMin = inputHandler.getInt();
                    } while (tempMin.status == FunctionReturnStatus::fail);
                    
                    InputIntResult tempMax;
                    do {
                        tempMax = inputHandler.getInt();
                    } while (tempMax.status == FunctionReturnStatus::fail);

                    if (tempMin.result == 0 || tempMax.result == 0) {
                        connectedHub->turnOffAlarms();
                        break;
                    }
                    connectedHub->setTemperatureAlarms(tempMin.result, tempMax.result);
                    connectedDisplay->printMessage("Temperature alarm set!");
                    inputCommand.status = FunctionReturnStatus::none;
                    break;
                }
                // if (inputCommand.result == "h") {
                //     connectedDisplay->printMessage("> Enter [low] then [high]\n> Enter [return] or [0] to turn alarms off.");
                //     InputIntResult humidMin = inputHandler.getInt();
                //     InputIntResult humidMax = inputHandler.getInt();
                //     if (humidMin.result == 0 || humidMax.result == 0) {
                //         connectedHub->turnOffAlarms();
                //         break;
                //     }
                //     connectedHub->setTemperatureAlarms(humidMin.result, humidMax.result);
                //     connectedDisplay->printMessage("Humidity alarm set!");
                //     break;
                // }
                break;
            } 
            case FunctionReturnStatus::fail: {
                connectedDisplay->printMessage("Please enter a valid command.\n");
                break;
            }
        }
    } while (inputCommand.status != FunctionReturnStatus::none);
}

std::vector<std::string> UiManager::buildValidInputs(const std::vector<std::string>& valids) {
    std::vector<std::string> validInputs;

    for (auto& v : valids) {
        validInputs.emplace_back(v);
    }
    for (const auto& s : connectedHub->getSensorsList()) {
            validInputs.emplace_back(std::to_string(s->getSensorId()));
        }
    return validInputs;
}