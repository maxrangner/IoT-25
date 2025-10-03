#include <iostream>

float inpValA{};
float inpValB{};
int menuChoice{};
float result{};
bool quit = false;
char op = ' ';

int inputNumbers();
float calculate(float a, float b, int choice, char& op);

int main() {
    std::cout << "ExtraCalc! \n";
    inputNumbers();

    while (1) {
        while (menuChoice < 1 || menuChoice > 6) {
            std::cout << "1. Addition   "
                      << "2. Subtraction   "
                      << "3. Multiplication   "
                      << "4. Divition   "
                      << "5. Enter new numbers   "
                      << "6. Quit: ";
            std::cin >> menuChoice;
        }

        switch (menuChoice) {
            case 1: case 2: case 3: case 4:
                result = calculate(inpValA, inpValB, menuChoice, op);
                std::cout << inpValA << " " << op << " " << inpValB << " = " << result;
                break;
            case 5: inputNumbers(); break;
            case 6: quit = true; break;
        }

        std::cout << "\n";
        menuChoice = 0;
        result = 0;
        if (quit) break;
    }
    std::cout << "Thanks!\n\n";
}

int inputNumbers() {
    std::cout << "Enter two numbers separated by a space: ";
    std::cin >> inpValA >> inpValB;
    return 0;
}

float calculate(float a, float b, int choice, char& op) {
    switch (choice) {
        case 1: op = '+'; return a + b;
        case 2: op = '-'; return a - b;
        case 3: op = '*'; return a * b;
        case 4: op = '/'; return a / b;
    }
}