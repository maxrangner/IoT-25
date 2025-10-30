#pragma once
#include <map>
#include <functional>

class UiManager {
    std::map<std::string, std::map<int, std::function<void()>>> menuMap;
public:
    UiManager();
    void menu(SensorHub& hub);
    void menuAction(SensorHub& hub, int chosenAction);
    void triggerFunction();
};