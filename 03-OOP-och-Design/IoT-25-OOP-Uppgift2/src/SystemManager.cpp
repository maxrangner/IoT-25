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
    const int updateIntervalMs = updateInterval * 1000;
    const int step = THREAD_SLEEP_MS;

    while (ui.isRunning()) {
        hub.readAllSensors();

        int waited = 0;
        while (waited < updateIntervalMs && ui.isRunning()) { 
            std::this_thread::sleep_for(std::chrono::milliseconds(step));
            waited += step;
        }
    }
}
