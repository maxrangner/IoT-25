#include "SystemManager.h"
#include <thread>
#include <mutex>
#include <atomic>

SystemManager::SystemManager() : ui(hub, display, log), hub(log) {
}

void SystemManager::run() {
    // Run sensorRead thread
    std::thread t(&SystemManager::sensorReadThread, this); // Starts thread that handles sensor interval updates.

    ui.greeting();
    ui.run(); // Main program loop.
    t.join();
    ui.quitProcess();
}

void SystemManager::sensorReadThread() {
    while (ui.isRunning()) {
        int updateInterval = hub.getUpdateInterval();
        hub.updateSensors(); // Not properly implemented yet.
        std::this_thread::sleep_for(std::chrono::seconds(updateInterval));
    }
}
