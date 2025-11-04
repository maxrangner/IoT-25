#include <iostream>
#include "UiManager.h"
#include "definitions.h"
#include "InputHandler.h"

UiManager::UiManager() {
    isRunning_ = true;
    // connectedHub = nullptr;
    // connectedDisplay = nullptr;
    menuChoice = MenuOptions::startOfMenu;
}
UiManager::UiManager(SensorHub& hub, Display& disp) {
    isRunning_ = true;
    connectedHub = &hub;
    connectedDisplay = &disp;
}

void UiManager::greeting() const {
    connectedDisplay->printHeader("Welcome!");
}

void UiManager::quitProcess() {}

bool UiManager::isRunning() const { return isRunning_; }

bool UiManager::run() {
    while(true) {
        connectedDisplay->printMenu();
        getMenuSelection();
        menuAction(); 
    }
}

void UiManager::getMenuSelection() {
    int min = static_cast<int>(MenuOptions::startOfMenu) + 1;
    int max = static_cast<int>(MenuOptions::endOfmenu) - 1;
    FunctionReturnStatus menuStatus;

    do {
        std::string userInput = "";
        std::cout << "> ";
        std::getline(std::cin, userInput);
        menuStatus = InputHandler.validateInt(userInput, min, max);

        if (menuStatus == FunctionReturnStatus::failInvalidInput) {
            std::string text = "Please enter a digit between " + std::to_string(min) + " and " + std::to_string(max) + ".";
            connectedDisplay->printMessage(text);
        } else if (menuStatus == FunctionReturnStatus::failOutOfRange) {
            std::string text = "Please enter a smaller number.";
            connectedDisplay->printMessage(text);
        }
    } while (menuStatus != FunctionReturnStatus::success);
}



void UiManager::menuAction() {
    switch (menuChoice) { 
        case MenuOptions::addRemove: std::cout << "addRemove\n"; connectedHub->addSensor(); break; // 1.
        case MenuOptions::updateInterval: std::cout << "updateInterval\n"; connectedHub->printAllInfo(); break; // 2.
        case MenuOptions::graph: break; // 3.
        case MenuOptions::stats: break; // 4.
        case MenuOptions::searchTime: break; // 5.
        case MenuOptions::searchVal: break; // 6.
        case MenuOptions::saveLoad: break; // 7.
        case MenuOptions::quit: isRunning_ = false; break; // 8.
    }
}
