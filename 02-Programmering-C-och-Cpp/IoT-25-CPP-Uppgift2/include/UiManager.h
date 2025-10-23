#ifndef UIMANAGER_HPP
#define UIMANAGER_HPP
#include <cfloat>
#include "definitions.h"
#include "functions.h"
#include "SystemManager.h"

class UiManager {
    private:
        void menuAction(SystemManager& manager, int chosenAction);

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
        void findData(SystemManager& manager);
        void saveSystemState(SystemManager& manager);
        void loadSystemState(SystemManager& manager);
        void menu(SystemManager& manager);
        std::string getInput(const std::vector<std::string>& valids, bool allowNonReturn = true);
        std::string getInput(float min, float max, bool allowNonReturn = true);
        std::string getInput(bool allowNonReturn = true);
};

#endif