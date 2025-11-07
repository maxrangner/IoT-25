#pragma once
#include "Sensor.h"
#include "SensorHub.h"
#include "UiManager.h"
#include "Display.h"
#include "Logger.h"
#include "utils.h"

class SystemManager {
    Logger log;
    SensorHub hub;
    Display display;
    UiManager ui;
public:
    SystemManager();
    void run();
    void sensorReadThread();
};