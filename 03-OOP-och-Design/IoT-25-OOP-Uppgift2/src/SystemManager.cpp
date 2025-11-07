#include "SystemManager.h"
#include <thread>
#include <mutex>
#include <atomic>

SystemManager::SystemManager() : hub(log), ui(hub, display, log){
}

void SystemManager::run() {
    std::thread t(&SystemManager::sensorReadThread, this);

    ui.greeting();
    ui.run();
    t.join();
    ui.quitProcess();
}

void SystemManager::sensorReadThread() {
    while (ui.isRunning()) {
        // hub.printAllInfo();
        hub.updateSensors();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
