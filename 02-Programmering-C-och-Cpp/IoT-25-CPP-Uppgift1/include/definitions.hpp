#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP
#include <ctime>

/*************************************************************************************
************************ CONSTANTS, VARIABLES AND DATASTRUCTS ************************
*************************************************************************************/

enum MenuSelection { // Menu options to be used in switch statement.
    add = 1, // 1.
    disp, // 2.
    graph, // 3.
    dispSorted, // 4.
    find, // 5.
    simulate, // 6.
    quit, // 7.
    endOfMenu // Not used, just to mark end of enum.
};

enum validatorType {
    wholeNum = 1,
    decimalNum,
    text
};

struct DataPoint { // Collection of data values to be stored in vector.
    float temperatureValue;
    struct tm datetime;
};

constexpr int MIN_MENU_OPTION = 1;
constexpr int MAX_MENU_OPTION = endOfMenu;
constexpr int MAX_DATA_POINTS = 5;
constexpr int CHAR_ARRAY_SIZE = 50;

#endif
