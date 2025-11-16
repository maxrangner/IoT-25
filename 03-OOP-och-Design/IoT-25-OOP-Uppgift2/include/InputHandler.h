#pragma once
#include <iostream>
#include "definitions.h"

class InputHandler {
public:
    void inputPause();
    InputIntResult getInt(int min = 0, int max = 0);
    InputStringResult getString(std::vector<std::string> valids = {}, bool allowNum = false);
};