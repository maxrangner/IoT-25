#include <iostream>
#include "UiManager.h"
#include "definitions.h"
#include "InputHandler.h"

UiManager::UiManager() {
    isRunning_ = true;
    // connectedHub = nullptr;
    // connectedDisplay = nullptr;
    // menuChoice = MenuOptions::startOfMenu;
}
UiManager::UiManager(SensorHub& hub, Display& disp) {
    isRunning_ = true;
    connectedHub = &hub;
    connectedDisplay = &disp;
}

void UiManager::greeting() const {
    connectedDisplay->printHeader("Welcome!");
}

void UiManager::quitProcess() {
    connectedDisplay->printMessage("Bye!");
}

bool UiManager::isRunning() const { return isRunning_; }

bool UiManager::run() {
    while(isRunning_) {
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
        case MenuOptions::updateInterval: std::cout << "updateInterval\n"; connectedHub->printAllInfo(); break; // 2.
        case MenuOptions::graph: break; // 3.
        case MenuOptions::stats: break; // 4.
        case MenuOptions::searchTime: break; // 5.
        case MenuOptions::searchVal: break; // 6.
        case MenuOptions::saveLoad: break; // 7.
        case MenuOptions::quit: quitProcess(); isRunning_ = false; break; // 8.
    }
}

void UiManager::addRemoveSensors() {
    connectedDisplay->printMessage("\nTo add sensor: [t]emperature sensor, [h]umidity sensor.\nTo remove: enter sensor Id.\nPress [return] to finish");
    InputStringResult inputCommand;
    std::vector<std::string> validInputs;

    do { // Loops until successful input
        validInputs.clear();
        for (const auto& s : connectedHub->getSensorsList()) {
            validInputs.emplace_back(s->getSensorId());
        }
        validInputs.emplace_back("t");
        validInputs.emplace_back("h");

        inputCommand = inputHandler.getString(validInputs);
        switch (inputCommand.status) {
            case FunctionReturnStatus::none: break;
            case FunctionReturnStatus::success: {
                if (inputCommand.result == "t") {
                    connectedHub->addSensor();
                }
                if (inputCommand.result == "h") {
                    connectedHub->addSensor();
                }
                break;
            } 
            case FunctionReturnStatus::fail: {
                std::string text = "Please enter a valid sensorId.";
                connectedDisplay->printMessage(text);
                break;
            }
        }
    } while (inputCommand.status != FunctionReturnStatus::none);
}