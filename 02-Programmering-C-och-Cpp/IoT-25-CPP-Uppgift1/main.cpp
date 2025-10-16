#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cctype>
#include "include/definitions.h"
#include "include/functions.h"

int menu() {
    int menuChoice = 0;
    std::string input;

    std::cout << "\n*********** MENU ***********\n"
              << "1. Add new values\n"
              << "2. Display statistics\n"
              << "3. Display graph * WIP *\n"
              << "4. Display values sorted\n"
              << "5. Find value\n"
              << "6. Simulate values\n"
              << "7. Quit\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (isValidInput(input, wholeNum, 1, 7)) {
            menuChoice = std::stoi(input);
            return menuChoice;
        }
    }
}

bool action(int chosenAction, std::vector<DataPoint>& data) {
    switch (chosenAction) {
        case addValues: uiAddValues(data); break;
        case dispStats: uiDisplayStats(data); break;
        case dispGraph: uiDisplayGraph(data); break; // WIP
        case dispSorted: uiDisplaySorted(data); break;
        case findValue: uiFindData(data); break;
        case simulateValues: uiGenerateDataPoints(data); break;
        case quit: return true;
    }
    return false;
}

int main() {
    std::vector<DataPoint> temperatureData;
    bool shouldQuit = false;

    while (!shouldQuit) {
        int choice = menu();
        shouldQuit = action(choice, temperatureData);
    }
    std::cout << "Bye!\n";
    return 0;
}
