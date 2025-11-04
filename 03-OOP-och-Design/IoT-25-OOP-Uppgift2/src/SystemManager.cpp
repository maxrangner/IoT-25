#include "SystemManager.h"

SystemManager::SystemManager() : ui(hub, display){
}

void SystemManager::run() {
    ui.greeting();
    ui.run();
    ui.quitProcess();
}
