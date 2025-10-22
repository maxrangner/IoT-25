#include <iostream>
#include <map>
#include <vector>

#include <ctime>
#include "SystemManager.h"
#include "functions.h"
#include "definitions.h"

bool isValidInput(const std::string& input, int typeSelector, float min, float max) {
    switch (typeSelector) {
        case wholeNum: {
            try {
                int inputVal = std::stoi(input);
                if (inputVal >= min && inputVal <= max) return true;
                std::cout << "Please enter a number between " << static_cast<int>(min) << " and " << static_cast<int>(max) << "\n";
            } catch (...) {
                std::cout << "Please enter a valid number.\n";
            }
            break;
        }
        case decimalNum: {
            try {
                float inputVal = std::stof(input);
                if (inputVal >= min && inputVal <= max) return true;
                std::cout << "Please enter a number between " << min << " and " << max << "\n";
            } catch (...) {
                std::cout << "Please enter a valid number.\n";
            }
            break;
        }
    };

    return false;
}