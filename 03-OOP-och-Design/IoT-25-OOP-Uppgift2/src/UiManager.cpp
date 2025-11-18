#include <iostream>
#include <thread>
#include "UiManager.h"
#include "definitions.h"
#include "InputHandler.h"
#include "utils.h"

UiManager::UiManager() : isRunning_(true), firstRun(true) {
}
UiManager::UiManager(SensorHub& hub, Display& disp, Logger& log)
    : isRunning_(true), firstRun(true), connectedHub(&hub), connectedDisplay(&disp), connectedLog(&log) {
}

// GETTERS
bool UiManager::isRunning() const { return isRunning_; }

// STARTUP & SHUTDOWN
void UiManager::greeting() const {
    connectedDisplay->printHeader("Welcome to the SensorHub!");
}

void UiManager::quitProcess() {
    connectedDisplay->printMessage("Bye!");
}

// CORE
void UiManager::run() {
    while(isRunning_) {
        if (!firstRun) {
             connectedDisplay->clear();
        }
        connectedDisplay->printMenu();
        MenuOptions choice = getMenuSelection();
        menuAction(choice); 
        firstRun = false;
    }
}

MenuOptions UiManager::getMenuSelection() {
    int menuMin = static_cast<int>(MenuOptions::startOfMenu) + 1;
    int menuMax = static_cast<int>(MenuOptions::endOfmenu) - 1;
    InputIntResult menuStatus;

    do { // Loops until successful input
        menuStatus = inputHandler.getInt(menuMin, menuMax);
        if (menuStatus.status == FunctionReturnStatus::fail) {
            std::string text = "Please enter a digit between " + std::to_string(menuMin) + " and " + std::to_string(menuMax) + ".";
            connectedDisplay->printMessage(text);
            connectedDisplay->printMessage("");
        }
    } while (menuStatus.status != FunctionReturnStatus::success);

    return static_cast<MenuOptions>(menuStatus.result);
}

void UiManager::menuAction(MenuOptions choice) {
    switch (choice) { 
        case MenuOptions::addRemove: addRemoveSensors(); break; // 1.
        case MenuOptions::statusScreen: statusScreen(); break; // 2. This is a temporary function. This will bring you to a status screen with all current data displayed.
        case MenuOptions::settings: setAlarms(); break; // 3. Not yet implemented.
        case MenuOptions::saveLoad: saveLoadData(); break; // 4. Not yet implemented.
        case MenuOptions::quit: isRunning_ = false; break; // 5.
    }
}

// ACTIONS
void UiManager::addRemoveSensors() {
    connectedDisplay->clear();
    connectedDisplay->printHeader("Add / Remove Sensors");
    InputStringResult inputCommand;
    std::vector<std::string> validInputs = buildValidInputs({"t", "h"});
    
    while (true) {
        connectedDisplay->printMessage("> Add [t]emperature sensor\n> Add [h]umidity sensor\n> To remove: enter sensor [Id]\n> Press [return] to finish.");

        // Loops until successful input
        do {
            inputCommand = inputHandler.getString(validInputs, true);
            if (inputCommand.status == FunctionReturnStatus::fail) {
                std::string text = "Please enter valid sensor type or sensor id.";

                connectedDisplay->printMessage(text);
                connectedDisplay->printMessage("");
            }
        } while (inputCommand.status == FunctionReturnStatus::fail);

        // User enter nothing
        if (inputCommand.result == "") break;

        // Add temperature sensor
        if (inputCommand.result == "t"){ 
            connectedHub->addSensor(SensorType::temperatureSensor);
            connectedDisplay->printMessage("Temperature sensor added");
            inputHandler.inputPause();
            continue;
        }

        // Add humidity sensor
        if (inputCommand.result == "h") { 
            connectedHub->addSensor(SensorType::humiditySensor);
            connectedDisplay->printMessage("Humidity sensor added");
            inputHandler.inputPause();
            continue;
        }

        // User enter id to delete sensor
        int sensorDelete = std::stoi(inputCommand.result);
        bool sensorFound = false;
        for (auto& s : connectedHub->getSensorsList()) {
            if (s->getSensorId() == sensorDelete) {
                sensorFound = true;
                break;
            }
        }
        if (sensorFound) {
            connectedHub->removeSensor(sensorDelete);
            std::string text = "Removed sensor with id: " + std::to_string(sensorDelete);
            connectedDisplay->printMessage(text);
        } else {
            std::string text = "No sensor with id: " + std::to_string(sensorDelete) + " found.";
            connectedDisplay->printMessage(text);
        }
        inputHandler.inputPause();
    }
}

void UiManager::statusScreen() {
    connectedDisplay->clear();
    connectedDisplay->printHeader("StatusScreen");
    InputStringResult inputCommand;
    std::vector<std::string> validInputs = buildValidInputs({"u"});
    
    static bool drawResult = false;
    int selectedSensorId = -1;

    // Loops until successful input
    while (true) {

        // Draw graph screen
        if (drawResult) {
                connectedDisplay->clear();
                connectedDisplay->printHeader("StatusScreen");
                connectedDisplay->printSensorsList(connectedLog->getLog(), connectedHub->getSensorsList(), connectedHub->getAlarms());
                connectedDisplay->drawGraph(connectedLog->getGraphData(selectedSensorId), connectedHub->getAlarms());
                connectedDisplay->printStats(connectedLog->getLog());
                connectedDisplay->printAlarms(connectedHub->getAlarms());
                drawResult = false;
            }
        
        // Loops until successful input
        do {
            if (drawResult) connectedDisplay->printMessage("> [num] sensorId.\n> [u]pdate.\n> [enter] to go back.");
            else connectedDisplay->printMessage("> Enter [num] sensorId.\n> [enter] to go back.");
            inputCommand = inputHandler.getString(validInputs);
            if (inputCommand.status == FunctionReturnStatus::fail) {
                connectedDisplay->printMessage("Please enter a valid command.\n");
            }
            
        } while (inputCommand.status == FunctionReturnStatus::fail);
        
        // User enter nothing
        if (inputCommand.result == "") break;

        // User updates
        if (inputCommand.result == "u") {
            if (selectedSensorId != -1) drawResult = true;
            else connectedDisplay->printMessage("");

        // User selects sensor
        } else {
            int sensorFound = false;
            int selectedSensor = std::stoi(inputCommand.result);
            for (auto& s : connectedHub->getSensorsList()) {
                if (s->getSensorId() == selectedSensor) {
                    sensorFound = true;
                    continue;;
                }
            }
            selectedSensorId = std::stoi(inputCommand.result);
            drawResult = true;
        }
    }
}

void UiManager::setAlarms() {
    connectedDisplay->printHeader("Set Alarms");
    connectedDisplay->printMessage("> Set [t]emperature sensor alarm\n> Set [h]umidity sensor alarm\n> [off] to turn alarms off\n> Press [return] to finish");
    InputStringResult inputCommand;
    std::vector<std::string> validInputs = buildValidInputs({"t", "h", "on", "off"});

    // Loops until successful input
    do {
        inputCommand = inputHandler.getString(validInputs);
        if (inputCommand.status == FunctionReturnStatus::fail) {
            connectedDisplay->printMessage("Please enter a valid command.\n");
        }
    } while (inputCommand.status == FunctionReturnStatus::fail);

    // User enter nothing
    if (inputCommand.result == "") return;

    // User turns on alarm
    if (inputCommand.result == "on") {
        connectedHub->turnAlarmsOn();
        connectedDisplay->printMessage("Alarms on");
        return;
    }

    // User turns off alarm
    if (inputCommand.result == "off") {
        connectedHub->turnAlarmsOff();
        connectedDisplay->printMessage("Alarms off");
        return;
    }
    
    // Setup alarms
    AlarmRangeResult newRange = setAlarmRange();
    if (newRange.status == FunctionReturnStatus::none) return;

    // Temperature alarm
    if (inputCommand.result == "t"){
        connectedHub->setTemperatureAlarms(newRange);
        connectedDisplay->printMessage("Temperature alarm set!");
        inputHandler.inputPause();
        return;
    }

    // Humidity alarm
    if (inputCommand.result == "h"){
        connectedHub->setHumidityAlarms(newRange);
        connectedDisplay->printMessage("Humidity alarm set!");
        inputHandler.inputPause();
        return;
    }
}

AlarmRangeResult UiManager::setAlarmRange() {
    AlarmRangeResult output;
    connectedDisplay->printMessage("> Enter [low] then [high]\n> [enter] to cancel.");
    
    // Set minimum
    InputIntResult alarmMin;
    do {
        alarmMin = inputHandler.getInt();
        if (alarmMin.status == FunctionReturnStatus::none) {
            output.status = FunctionReturnStatus::none;
            return output;
        }
    } while (alarmMin.status == FunctionReturnStatus::fail);
    
    // Set maximum
    InputIntResult alarmMax;
    while (true) {
        alarmMax = inputHandler.getInt();
        if (alarmMax.status == FunctionReturnStatus::none) {
            output.status = FunctionReturnStatus::none;
            return output;
        }
        if (alarmMax.status == FunctionReturnStatus::fail) continue;
        if (alarmMax.result <= alarmMin.result) {
            connectedDisplay->printMessage("Enter value greater than " + std::to_string(alarmMin.result));
            continue;
        }
        break;
    } 
    output.low = alarmMin.result;
    output.high = alarmMax.result;
    output.status = FunctionReturnStatus::success;

    return output;
}

void UiManager::saveLoadData() {
    connectedDisplay->printHeader("Save / Load data");
    connectedDisplay->printMessage("> [s]ave or [l]oad");
    InputStringResult inputCommand;
    std::vector<std::string> validInputs = buildValidInputs({"s", "l"});

    // Loops until successful input
    do { 
        inputCommand = inputHandler.getString(validInputs);
        if (inputCommand.status == FunctionReturnStatus::fail) {
            std::string text = "Please enter [" + validInputs[0] + "]ave or [" + validInputs[1] + "]oad.";
            connectedDisplay->printMessage(text);
            connectedDisplay->printMessage("");
        }
    } while (inputCommand.status == FunctionReturnStatus::fail);

    // Save
    if (inputCommand.result == "s") {
        connectedLog->saveData();
        connectedDisplay->printMessage("Data saved to file.");
    } 

    // Load
    if (inputCommand.result == "l") {
        connectedLog->loadData();
        connectedHub->restoreSensors();
        connectedDisplay->printMessage("Data loaded from file.");
    }
    inputHandler.inputPause();
}

std::vector<std::string> UiManager::buildValidInputs(const std::vector<std::string>& valids) {
    std::vector<std::string> validInputs;

    for (auto& v : valids) {
        validInputs.emplace_back(v);
    }
    for (const auto& s : connectedHub->getSensorsList()) {
            validInputs.emplace_back(std::to_string(s->getSensorId()));
        }
    return validInputs;
}