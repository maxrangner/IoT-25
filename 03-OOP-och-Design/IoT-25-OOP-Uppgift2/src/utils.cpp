#include <string>
#include "utils.h"
#include "definitions.h"

std::string makeLower(std::string input) {
    std::string output = "";
    for (const char& c : input) {
        output += std::tolower(c);
    }
    return output;
}