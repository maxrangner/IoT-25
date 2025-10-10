#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cctype>
#include "definitions.hpp"
#include "functions.hpp"

/***********************************************************
************************ ESSENTIALS ************************
***********************************************************/

int menu() { // Display menu and validate input.
    int menuChoice = 0;
    std::string input;

    std::cout << "\nMENU\n"
              << "1. Add new values\n"
              << "2. Display statistics\n"
              << "3. Display graph\n"
              << "4. Display values sorted\n"
              << "5. Find value\n"
              << "6. Simulate values\n"
              << "7. Quit";

    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, input);

        try {
            menuChoice = std::stoi(input);
            if (menuChoice >= MIN_MENU_OPTION && menuChoice <= MAX_MENU_OPTION) {
                return menuChoice;
            }
            std::cout << "Please enter a number between 1-7.\n";
        } catch (...) {
            std::cout << "Please enter a valid number.\n";
        }
    }
}

bool action(int chosenAction, std::vector<DataPoint>& data) {
    switch (chosenAction) {
        case add: addValues(data); break;
        case disp: calcStats(data); break;
        case graph: break; // WORK IN PROGRESS
        case dispSorted: sortData(data); break;
        case find: findDataPoint(data); break;
        case simulate: break; // WORK IN PROGRESS
        case quit: return true;
    }
    return false;
}

/*****************************************************
************************ MAIN ************************
/****************************************************/

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