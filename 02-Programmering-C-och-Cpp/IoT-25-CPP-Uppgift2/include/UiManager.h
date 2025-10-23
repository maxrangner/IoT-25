#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP
#include <cfloat>
#include "definitions.h"
#include "functions.h"
#include "SystemManager.h"

class UiManager {
    private:
        void menuAction(SystemManager& manager, int chosenAction);
        bool isValidNum(const std::string& inpStr, float min = -FLT_MAX, float max = FLT_MAX);
        bool isValidChoice(const std::string& inpStr, const std::vector<std::string>& valids);
    public:
        UiManager();
        bool isRunning;
        void addSensor(SystemManager& manager);
        void removeSensor(SystemManager& manager);
        void collectReadings(SystemManager& manager);
        void setSensorValue(SystemManager& manager);
        void displayData(SystemManager& manager);
        void displayStats(SystemManager& manager);
        void sortData(SystemManager& manager);
        void saveData(SystemManager& manager);
        void loadData(SystemManager& manager);
        void menu(SystemManager& manager);
        std::string getInput(const std::vector<std::string>& valids, bool allowNonReturn = true);
        std::string getInput(float min = -FLT_MAX, float max = FLT_MAX, bool allowNonReturn = true);
};

#endif