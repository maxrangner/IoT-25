#include <cctype>
#include <algorithm>
#include <vector>
#include "InputHandler.h"
#include "definitions.h"
#include "utils.h"

InputIntResult InputHandler::getInt(int min, int max) {
    InputIntResult output;
    output.result = 0;
    std::string userInput = "";

    std::cout << "\n\033[30;47m > \033[0m ";
    std::getline(std::cin, userInput);
    if (userInput == "") { // Return if input is empty.
        output.status = FunctionReturnStatus::success;
        return output;
    }
    if (std::all_of(userInput.begin(), userInput.end(), ::isdigit)) { // If input is all digits.
        int convertedInput = std::stoi(userInput);
        if (!(min == max) && ((convertedInput < min) || (convertedInput > max))) {
            output.status = FunctionReturnStatus::fail;
            return output;
        }
        output.result = convertedInput;
        output.status = FunctionReturnStatus::success;
        return output;
    }
    output.status = FunctionReturnStatus::fail;
    std::cout << "fail" << std::endl;
    return output;
}

InputStringResult InputHandler::getString(std::vector<std::string> valids) {
    InputStringResult output;
    output.result = "";
    std::string userInput = "";

    std::cout << "\n\033[30;47m > \033[0m ";
    std::getline(std::cin, userInput);
    if (userInput == "") { // Return if input is empty.
        output.status = FunctionReturnStatus::none;
        return output;
    }
    for (const std::string& s : valids) { // Loops through vector of accepted inputs and looks for match.
        if (makeLower(userInput) == s) {
            output.result = userInput;
            output.status = FunctionReturnStatus::success;
            return output;
        }
    }
    output.status = FunctionReturnStatus::fail;
    return output; 
}
