#include <iostream>
#include <iomanip>
#include "UiManager.h"
#include "SensorHub.h"

UiManager::UiManager(SensorHub& hub) {
    menuMap["1"] = hub.addSensor;
}

void UiManager::menu(SensorHub& hub) {
    int spacing = 4;

    std::cout << "\n*--- MENU ---*\n"
              << std::left << std::setw(spacing) << "1." << "Setup: Add / remove sensor\n"
              << std::left << std::setw(spacing) << "2." << "Setup: Update interval\n"
              << std::left << std::setw(spacing) << "3." << "Display: Historical Graph\n"
              << std::left << std::setw(spacing) << "4." << "Display: Statistics\n"
              << std::left << std::setw(spacing) << "5." << "Search: By time\n"
              << std::left << std::setw(spacing) << "6." << "Search: By value\n"
              << std::left << std::setw(spacing) << "7." << "Save / load System State\n"
              << std::left << std::setw(spacing) << "8." << "Quit\n"
              << "*-----------*" << std::endl;
    
    // menuSelection("1");
}
void UiManager::menuAction(SensorHub& hub, int chosenAction) {
    switch (chosenAction) { 
        case 1: break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: break;
        case 7: break;
        case 8: isRunning = false;
    }
}
}
void UiManager::triggerFunction() {}