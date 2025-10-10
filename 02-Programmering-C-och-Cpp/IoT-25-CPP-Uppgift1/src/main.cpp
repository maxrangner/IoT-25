#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cctype>
#include "definitions.hpp"
#include "functions.hpp"

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
