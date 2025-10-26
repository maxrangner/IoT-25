#include <iostream>
#include "functions.h"

bool isAcceptedComponent(std::string input, const std::vector<std::string>& acceptedComponents) {
    for (const std::string& s : acceptedComponents) {
        if (input == s) return true;
    }
    return false;
}