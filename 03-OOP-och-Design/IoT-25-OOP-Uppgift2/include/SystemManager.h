#pragma once
#include "Sensor.h"
#include "SensorHub.h"
#include "UiManager.h"
#include "Display.h"
#include "Logger.h"
#include "utils.h"

class SystemManager {
    SensorHub hub;
    Display display;
    Logger log;
    UiManager ui;
public:
    SystemManager();
    void run();
    void sensorReadThread();
};