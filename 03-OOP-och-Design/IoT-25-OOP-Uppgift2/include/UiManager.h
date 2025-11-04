#pragma once
#include "SensorHub.h"
#include "Display.h"
#include "definitions.h"

class UiManager {
    bool isRunning_;
    SensorHub* connectedHub;
    Display* connectedDisplay;
    MenuOptions menuChoice;
    InputHandler InputHandler;
public:
    UiManager();  
    UiManager(SensorHub& hub, Display& disp);
    void greeting() const;
    void quitProcess();
    bool isRunning() const;
    bool run();
    void getMenuSelection();
    FunctionReturnStatus isValidInt(std::string input, int min, int max);
    void menuAction();
};