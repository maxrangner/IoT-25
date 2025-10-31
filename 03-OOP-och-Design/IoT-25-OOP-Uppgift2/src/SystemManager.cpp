#include "SystemManager.h"

SystemManager::SystemManager() : ui(hub, display){
}


void SystemManager::run() {
    std::string temp;
    while(true) {
        ui.menu();
        std::cin >> temp;
    }
}
