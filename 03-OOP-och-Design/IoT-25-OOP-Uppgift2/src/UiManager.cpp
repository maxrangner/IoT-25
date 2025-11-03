#include <iostream>
#include "UiManager.h"
#include "definitions.h"

UiManager::UiManager() {
    isRunning_ = true;
    // connectedHub = nullptr;
    // connectedDisplay = nullptr;
    menuChoice = 0;
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
        getMenuInput();
        menuAction(); 
    }

}
void UiManager::menuAction() {
    switch (menuChoice) { 
        case MenuOptions::addRemove: std::cout << "addRemove"; break; // 1.
        case MenuOptions::updateInterval: std::cout << "updateInterval"; break; // 2.
        case MenuOptions::graph: break; // 3.
        case MenuOptions::stats: break; // 4.
        case MenuOptions::searchTime: break; // 5.
        case MenuOptions::searchVal: break; // 6.
        case MenuOptions::saveLoad: break; // 7.
        case MenuOptions::quit: isRunning_ = false; break; // 8.
    }
}

void UiManager::getMenuInput() {
    std::string userInput = "";
    int min = MenuOptions::startOfMenu;
    int max = MenuOptions::endOfmenu;
    while(true) {
        std::cout << "> ";
        std::getline(std::cin, userInput);
        try {
            int convertedUserInput = std::stoi(userInput);
            if (!isValidInt(convertedUserInput, min, max)) {
                throw std::invalid_argument("");
            }
            menuChoice = convertedUserInput;
            break;
        } catch (...) {
            std::cout << "Please enter a digit between " << min + 1 << " and " << max - 1 << std::endl;
        }
    }
}

bool UiManager::isValidInt(int input, int min, int max) {
    if (input > min && input < max) {
        return true;
    } else return false;
}

bool UiManager::isValidInt(std::string input, int min, int max) {
    int convertedInput = std::stoi(input);
    if (convertedInput > min && convertedInput < max) {
        return true;
    } else return false;
}