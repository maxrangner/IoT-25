#pragma once
#include "SensorHub.h"
#include "Display.h"
#include "InputHandler.h"
#include "definitions.h"
#include "Logger.h"

class UiManager {
    // VARIABLES
    bool isRunning_;
    bool firstRun;
    MenuOptions menuChoice;
    InputHandler inputHandler;

    // SYSTEM
    SensorHub* connectedHub;
    Display* connectedDisplay;
    Logger* connectedLog;

public:
    // CONSTRUCTORS
    UiManager();  
    UiManager(SensorHub& hub, Display& disp, Logger& log);

    // GETTERS
    bool isRunning() const;

    // STARTUP & SHUTDOWN
    void greeting() const;
    void quitProcess();
    
    // CORE
    void run();
    MenuOptions getMenuSelection();
    void menuAction(MenuOptions choice);

    // ACTIONS
    void addRemoveSensors();
    void statusScreen();
    void setAlarms();
    AlarmRangeResult setAlarmRange();
    void saveLoadData();

    // UTILS
    std::vector<std::string> buildValidInputs(const std::vector<std::string>& valids);
};