#pragma once
#include <iostream>
#include "definitions.h"

class InputHandler {
public:
    InputIntResult getInt(int min = 0, int max = 0);
    InputStringResult getString(std::vector<std::string> valids = {});
    // InputIntOrStringResult getIntOrString(int min = 0, int max = 0, std::vector<std::string> valids);
};