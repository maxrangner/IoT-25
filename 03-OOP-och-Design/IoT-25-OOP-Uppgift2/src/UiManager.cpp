#include <iostream>
#include "UiManager.h"

UiManager::UiManager() {
    isRunning = true;
    connectedHub = nullptr;
    connectedDisplay = nullptr;
}
UiManager::UiManager(SensorHub& hub, Display& disp) {
    isRunning = true;
    connectedHub = &hub;
    connectedDisplay = &disp;
}

void UiManager::greeting() {
    connectedDisplay->printHeader("Welcome!");
}

void UiManager::menu() {
    if (connectedDisplay == nullptr) {
       std::cout << "No display setup." << std::endl;
       return;
    }
    connectedDisplay->printMenu();
}
void UiManager::menuAction() {
    // switch () { 
    //     case 1: break;
    //     case 2: break;
    //     case 3: break;
    //     case 4: break;
    //     case 5: break;
    //     case 6: break;
    //     case 7: break;
    //     case 8: isRunning = false; break;
    // }
}

void UiManager::getMenuInput() {

}