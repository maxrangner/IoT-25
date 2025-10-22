#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP
#include "definitions.h"
#include "SystemManager.h"

class UiManager {
    private:
        bool menuAction(SystemManager& manager, int chosenAction);
        // bool isValidNum(std::string inpStr, float min = -FLT_MAX, float max = FLT_MAX);
        bool isValidChoice(const std::string& inpStr, const std::vector<std::string>& valids);
    public:
        UiManager();
        bool isRunning;
        void addSensor(SystemManager& manager);
        void collectReadings(SystemManager& manager);
        void displayData(SystemManager& manager);
        void saveData(SystemManager& manager);
        void loadData(SystemManager& manager);
        void menu(SystemManager& manager);
};

#endif