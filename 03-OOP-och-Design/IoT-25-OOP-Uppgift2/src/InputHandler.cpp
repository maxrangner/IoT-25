#include "InputHandler.h"
#include "definitions.h"

FunctionReturnStatus validateInt(std::string input, int min, int max) {
    try {
        int convertedInput = std::stoi(input);
        if ((convertedInput < min) || (convertedInput > max)) {
            throw std::invalid_argument("");
        }
        menuChoice = static_cast<MenuOptions>(convertedInput);
        return FunctionReturnStatus::success;
    } catch (const std::invalid_argument& e) {
        return FunctionReturnStatus::failInvalidInput;
    } catch (const std::out_of_range& e) {
        return FunctionReturnStatus::failOutOfRange;    
    }
}
