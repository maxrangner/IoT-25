#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP
#include <ctime>
#include <random>

/*************************************************************************************
************************ CONSTANTS, VARIABLES AND DATASTRUCTS ************************
*************************************************************************************/

enum MenuSelection { // Menu options to be used in switch statement.
    startofMenu, // 0.
    addValues, // 1.
    dispData, // 2.
    dispStats, // 3.
    dispGraph, // 4.
    dispSorted, // 5.
    findValue, // 6.
    simulateValues, // 7.
    quit, // 8.
    endOfMenu // Not used, just to mark end of enum.
};

enum validatorType {
    wholeNum = 1, // 1.
    decimalNum, // 2.
    text // 3.
};

struct DataPoint { // Collection of data values to be stored in vector.
    float temperatureValue;
    struct tm datetime;
};

struct Statistics {
    bool empty = true;
    int numDataPoints = 0;
    double sum = 0.0;
    double average = 0.0;
    double variance = 0.0;
    float stdDeviation = 0.0f;
    float minVal = 0.0f;
    float maxVal = 0.0f;
};

constexpr int MIN_MENU_OPTION = 1;
constexpr int MAX_MENU_OPTION = endOfMenu;
constexpr int MAX_DATA_POINTS = 5;
constexpr int CHAR_ARRAY_SIZE = 50;
constexpr int MONTH_IN_SEC = 2592000; // One month (30 days) in seconds

#endif
