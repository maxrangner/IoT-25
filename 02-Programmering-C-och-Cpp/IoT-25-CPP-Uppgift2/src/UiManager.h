#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP
#include <cfloat>
#include "definitions.h"
#include "functions.h"
#include "SystemManager.h"

class UiManager {
    private:
        bool menuAction(SystemManager& manager, int chosenAction);
        bool isValidNum(const std::string& inpStr, float min = -FLT_MAX, float max = FLT_MAX);
        bool isValidChoice(const std::string& inpStr, const std::vector<std::string>& valids);
    public:
        UiManager();
        bool isRunning;
        void addSensor(SystemManager& manager);
        void removeSensor(SystemManager& manager);
        void collectReadings(SystemManager& manager);
        void displayData(SystemManager& manager);
        void saveData(SystemManager& manager);
        void loadData(SystemManager& manager);
        void menu(SystemManager& manager);
        std::string getInput(std::vector<std::string> valids);
        std::string getInput(float min, float max);
};

#endif