#include <iostream>
#include <string>
#include <vector>

enum MenuSelection {
    add = 1, // 1.
    disp, // 2.
    find, // 3.
    dispSorted, // 4.
    quit // 5.
};
const int MIN_MENU_OPTION = 1;
const int MAX_MENU_OPTION = 5;

void addValues(std::vector<float>& data) {
    std::cout << "Add new values\n\n";
}

void displayValues(const std::vector<float>& data) {
    // TEMP
}

int menu() {
    int menuChoice {};
    std::string input;

    std::cout << "MENU\n"
              << "1. Add new values\n"
              << "2. Display statistics\n"
              << "3. Find value\n"
              << "4. Display values sorted\n"
              << "5. Quit\n";

    while (true) {
        std::cout << "\nOption: ";
        std::getline(std::cin, input);

        try {
            menuChoice = std::stoi(input);
            if (menuChoice >= MIN_MENU_OPTION && menuChoice <= MAX_MENU_OPTION) {
                return menuChoice;
            }
            std::cout << "Please enter a number between 1-5.\n";
        } catch (...) {
            std::cout << "Please enter a valid number.\n";
        }
    }
}

bool action(int chosenAction, std::vector<float>& data) {
    switch (chosenAction) {
        case add: addValues(data); break;
        case disp: displayValues(data); break;
        case find: break; // TEMP
        case dispSorted: break; // TEMP
        case quit: return true;
    }
    return false;
}

int main() {
    std::vector<float> temperatureData;
    bool shouldQuit = false;

    while (!shouldQuit) {
        int choice = menu();
        shouldQuit = action(choice, temperatureData);
    }
    std::cout << "Bye!\n";
    return 0;
}