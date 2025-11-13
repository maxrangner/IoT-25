#include "SystemManager.h"
#include <thread>
#include <mutex>
#include <atomic>

SystemManager::SystemManager() : log(display), ui(hub, display, log), hub(log) {
    updateInterval = 5; // Seconds
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
        hub.readAllSensors();

        std::this_thread::sleep_for(std::chrono::seconds(updateInterval));
    }
}
