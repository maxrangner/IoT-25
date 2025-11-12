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

void UiManager::greeting() const {
    connectedDisplay->printHeader("Welcome!");
}

void UiManager::quitProcess() {
    connectedDisplay->printMessage("Bye!");
}

bool UiManager::isRunning() const { return isRunning_; }

void UiManager::run() {
    while(isRunning_) {
        // connectedDisplay->clear(); // Not yet implementet.
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
        }
    } while (menuStatus.status != FunctionReturnStatus::success);

    return static_cast<MenuOptions>(menuStatus.result);
}


void UiManager::menuAction(MenuOptions choice) {
    switch (choice) { 
        case MenuOptions::addRemove: addRemoveSensors(); break; // 1.
        case MenuOptions::statusScreen: statusScreen(); break; // 2. This is a temporary function. This will bring you to a status screen with all current data displayed.
        case MenuOptions::searchMeasure: break; // 3. Not yet implemented.
        case MenuOptions::settings: break; // 4. Not yet implemented.
        case MenuOptions::saveLoad: break; // 5. Not yet implemented.
        case MenuOptions::quit: isRunning_ = false; break; // 6.
    }
}

void UiManager::addRemoveSensors() {
    connectedDisplay->printHeader("Add / Remove Sensors");
    connectedDisplay->printMessage("To add sensor: [t]emperature sensor, [h]umidity sensor.\nTo remove: enter sensor Id.\nPress [return] to finish.");
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
                connectedDisplay->printMessage("Please enter a valid command.");
                break;
            }
        }
    } while (inputCommand.status != FunctionReturnStatus::none);
}

void UiManager::printAllSensorInfo() {
    for (auto& s : connectedHub->getSensorsList()) {
        std::cout << "Sensor:\n";
        for (auto& e : s->getInfo()) {
            connectedDisplay->printMessage(e.first, false);
            connectedDisplay->printMessage(": ", false);
            connectedDisplay->printMessage(e.second);
        }
        std::cout << "\n";
    }
    connectedDisplay->printMessage("\n*************************************\n");
}

void UiManager::statusScreen() {
    while (true) {
        connectedDisplay->clear();
        connectedDisplay->drawGraph(connectedLog->getGraphData(), 0);

        std::this_thread::sleep_for(std::chrono::seconds(connectedHub->getUpdateInterval()));
    }
}