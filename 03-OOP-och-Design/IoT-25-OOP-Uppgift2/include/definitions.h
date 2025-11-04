#pragma once

enum class MenuOptions {
    startOfMenu, // 0.
    addRemove, // 1.
    updateInterval, // 2.
    graph, // 3.
    stats, // 4.
    searchTime, //5. 
    searchVal, // 6.
    saveLoad, // 7.
    quit, // 8.
    endOfmenu // 9.
};

enum class FunctionReturnStatus {
    success,
    fail,
    none
    // failInvalidInput,
    // failOutOfRange
};

struct InputIntResult {
    FunctionReturnStatus status;
    int result;
};

struct InputStringResult {
    FunctionReturnStatus status;
    std::string result;
};

struct InputIntOrStringResult {
    FunctionReturnStatus status;
    std::string result;
};