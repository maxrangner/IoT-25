#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cctype>
#include "src/definitions.h"
#include "src/functions.h"

int menu() {
    int menuChoice = 0;
    std::string input;

    std::cout << "\n*********** MENU ***********\n"
              << "1. Add new values\n"
              << "2. Display current data\n"
              << "3. Display statistics\n"
              << "4. Display graph * WIP *\n"
              << "5. Display values sorted\n"
              << "6. Find value\n"
              << "7. Simulate values\n"
              << "8. Quit\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input); // Used getline instead of cin to skip handling input stream buffer menually.

        if (isValidInput(input, wholeNum, startofMenu + 1, endOfMenu - 1)) { // Utilizes enum MenuSelection to dynamically get span of valid input.
            menuChoice = std::stoi(input); // Casts input string to int. It's safe because it's been validated by isValidInput().
            return menuChoice;
        }
    }
}

bool action(int chosenAction, std::vector<DataPoint>& data) {
    switch (chosenAction) { // Uses enum MenuSelection to make switch case easier to read.
        case addValues: uiAddValues(data); break;
        case dispData: uiDisplayData(data); break;
        case dispStats: uiDisplayStats(data); break;
        case dispGraph: uiDisplayGraph(data); break; // WIP
        case dispSorted: uiDisplaySorted(data); break;
        case findValue: uiFindData(data); break;
        case simulateValues: uiGenerateDataPoints(data); break;
        case quit: return true;
    }
    return false; // Return false to NOT trigger program quit in main loop.
}

int main() {
    std::vector<DataPoint> temperatureData; // Start of program declares a vector of the struct DataPoint. Left intentionally empty so UI functions can trigger a print out "No data saved".
    bool shouldQuit = false;

    while (!shouldQuit) {
        int choice = menu();
        shouldQuit = action(choice, temperatureData); // action() is our main entry point for our vector database (temperatureData) to be fed to the varous functions.
    }
    std::cout << "Bye!\n";
    return 0;
}
