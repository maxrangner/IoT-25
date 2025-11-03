#pragma once
#include "SensorHub.h"
#include "Display.h"

class UiManager {
    bool isRunning_;
    SensorHub* connectedHub;
    Display* connectedDisplay;
    int menuChoice;
public:
    UiManager();  
    UiManager(SensorHub& hub, Display& disp);
    void greeting() const;
    void quitProcess();
    bool isRunning() const;
    bool run();
    void menuAction();
    void getMenuInput();
    bool isValidInt(int input, int min, int max);
    bool isValidInt(std::string input, int min, int max);
};