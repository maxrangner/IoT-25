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

    std::cout << "> ";
    std::getline(std::cin, userInput);
    if (std::all_of(userInput.begin(), userInput.end(), ::isdigit)) {
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
    return output;
}

InputStringResult InputHandler::getString(std::vector<std::string> valids) {
    InputStringResult output;
    output.result = "";
    std::string userInput = "";

    std::cout << "> ";
    std::getline(std::cin, userInput);
    if (userInput == "") {
        output.status = FunctionReturnStatus::none;
        return output;
    }
    for (const std::string& s : valids) {
        if (makeLower(userInput) == s) {
            output.result = userInput;
            output.status = FunctionReturnStatus::success;
            return output;
        }
    }
    output.status = FunctionReturnStatus::fail;
    return output; 
}

// InputIntOrStringResult InputHandler::getIntOrString(int min, int max, std::vector<std::string> valids) {
//     InputIntOrStringResult output;
//     output.result = "";
//     std::string userInput = "";

//     while (true) {
//         std::cout << "> ";
//         std::getline(std::cin, userInput);

//         if (std::all_of(userInput.begin(), userInput.end(), ::isdigit)) {
//             int convertedInput = std::stoi(userInput);
//             if (!(min == max) && ((convertedInput < min) || (convertedInput > max))) {
//                 output.status = FunctionReturnStatus::failInvalidInput;
//                 return output;
//             }
//             output.result = userInput;
//             output.status = FunctionReturnStatus::success;
//             return output;
//         } else {
//             for (const std::string& s : valids) {
//                 if (makeLower(userInput) == s) {
//                     output.result = userInput;
//                     output.status = FunctionReturnStatus::success;
//                     return output;
//                 }
//             }
//             output.status = FunctionReturnStatus::failInvalidInput;
//             return output;
//         }
//     }
// }