#include "SystemManager.h"
#include <thread>
#include <mutex>
#include <atomic>

SystemManager::SystemManager() : hub(log), ui(hub, display, log){
}

void SystemManager::run() {
    std::thread t(&SystemManager::sensorReadThread, this); // Starts thread that handles sensor interval updates.

    ui.greeting();
    ui.run(); // Main program loop.
    t.join();
    ui.quitProcess();
}

void SystemManager::sensorReadThread() {
    while (ui.isRunning()) {
        hub.updateSensors(); // Not properly implemented yet.
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
