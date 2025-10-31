#pragma once
#include "SensorHub.h"
#include "Display.h"

class UiManager {
    bool isRunning;
    SensorHub* connectedHub;
    Display* connectedDisplay;
public:
    UiManager();  
    UiManager(SensorHub& hub, Display& disp);
    void greeting();
    void menu();
    void menuAction();
    void getMenuInput();
};