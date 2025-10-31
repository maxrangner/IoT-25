#pragma once
#include "Sensor.h"
#include "SensorHub.h"
#include "UiManager.h"
#include "Display.h"
#include "utils.h"

class SystemManager {
    SensorHub hub;
    Display display;
    UiManager ui;
public:
    SystemManager();
    void run();
};