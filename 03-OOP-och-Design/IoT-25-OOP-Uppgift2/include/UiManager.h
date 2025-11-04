#pragma once
#include "SensorHub.h"
#include "Display.h"
#include "InputHandler.h"
#include "definitions.h"

class UiManager {
    // VARIABLES
    bool isRunning_;
    MenuOptions menuChoice;
    InputHandler inputHandler;

    // SYSTEM
    SensorHub* connectedHub;
    Display* connectedDisplay;

public:
    // CONSTRUCTORS
    UiManager();  
    UiManager(SensorHub& hub, Display& disp);

    // GETTERS
    bool isRunning() const;

    // STARTUP & SHUTDOWN
    void greeting() const;
    void quitProcess();
    
    // CORE
    bool run();
    MenuOptions getMenuSelection();
    void menuAction(MenuOptions choice);

    // ACTIONS
    void addRemoveSensors();
};