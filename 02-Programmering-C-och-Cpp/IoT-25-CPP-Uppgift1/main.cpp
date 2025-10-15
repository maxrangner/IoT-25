#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cctype>
#include "include/definitions.hpp"
#include "include/functions.hpp"

int menu() { // Display menu. Returns valid menu choice.
    int menuChoice = 0;
    std::string input;

    std::cout << "\n*********** MENU ***********\n"
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

bool action(int chosenAction, std::vector<DataPoint>& data) { // Executes action based on menu choice. Returns true to quit.
    switch (chosenAction) {
        case add: uiAddValues(data); break;
        case disp: break;
        case graph: break; // WORK IN PROGRESS
        case dispSorted: break;
        case find: break;
        case simulate: generateDataPoints(data); break;
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
