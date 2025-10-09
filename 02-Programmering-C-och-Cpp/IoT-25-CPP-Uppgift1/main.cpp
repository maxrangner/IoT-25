#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <cctype>
#include <algorithm>

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
    quit // 7.
};

struct DataPoint { // Collection of data values to be stored in vector.
    float tempValue;
    struct tm datetime;
};

constexpr int MIN_MENU_OPTION = 1;
constexpr int MAX_MENU_OPTION = 7;
constexpr int MAX_DATA_POINTS = 5;
constexpr int CHAR_ARRAY_SIZE = 50;

/**********************************************************************
************************ FUNCTION DECLARATIONS ************************
/*********************************************************************/

void printData(const std::vector<DataPoint>& data);

/******************************************************
************************ TOOLS ************************
******************************************************/

struct tm getTime() { // Gets current time from <ctime> module. Returns tm struct.
    std::time_t timestamp = time(nullptr);
    struct tm currentTime = *localtime(&timestamp);

    return currentTime;
}

bool isTempValue(const std::string& userInp) { // Checks if string is a valid temperature value. Returns true/false.
    try {
        std::stof(userInp);
        return true;
    } catch (...) {
        return false;
    }
}

bool isDate(const std::string& userInp) { // Checks if string is a valid date. Returns true/false.
    if (userInp.length() != 10) return false;
    if (userInp.at(4) != '/' || userInp.at(7) != '/') return false;
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7 && !std::isdigit(userInp[i])) return false;
    }
    return true;
}

/*************************************************************
************************* FUNCTIONS **************************
/************************************************************/

void addValues(std::vector<DataPoint>& data) { // Adds values to the temperatureData vector.
    std::string userInp {};
    std::cout << "Add new value. If finished, type \"done\": \n";

    while(true) { // Loops until fed with valid input.
        std::cout << "> ";
        std::getline(std::cin, userInp);
        if (userInp == "done") break;
        DataPoint newDataPoint;

        try { // Tries to cast input string as float. Propts user if fails.
            newDataPoint.tempValue = std::stof(userInp);
        } catch (...) {
            std::cout << "Please enter a valid number.\n";
            continue;
        }
        
        newDataPoint.datetime = getTime(); // Adds timestamp to new temperature value.

        if (data.size() >= MAX_DATA_POINTS) { // Checks if vector is too big, and limits it to MAX_DATA_POINTS.
            data.erase(data.begin());
        }
        data.push_back(newDataPoint);
    }

    printData(data);
}

void calcStats(const std::vector<DataPoint>& data) { // Calculates and displays statistics based on data in vector.
    int numDataPoints = data.size();
    double sum {};
    double average {};
    double sumVariance {};
    float variance {};
    float stdDeviation {};
    int count = 1;
    float minVal = data[0].tempValue;
    float maxVal = data[0].tempValue;

    printData(data);

    for (const DataPoint& d : data) { // Calculates sum and min/max values.
        sum += d.tempValue;
        if (d.tempValue < minVal) {
            minVal = d.tempValue;
        }
        if (d.tempValue > maxVal) {
            maxVal = d.tempValue;
        } 
    }

    average = sum / numDataPoints;

    for (const DataPoint& d : data) {
        sumVariance += (d.tempValue - average) * (d.tempValue - average);
    }

    sumVariance = sumVariance / numDataPoints;
    stdDeviation = std::sqrt(sumVariance);

    std::cout << "\n" << numDataPoints << " datapoints registered." << std::endl;
    std::cout << sum << " is the total sum of registered values." << std::endl;
    std::cout << average << " is the average value." << std::endl;
    std::cout << minVal << " is the lowest measured value, and " << maxVal << " is the highest." << std::endl;
    std::cout << sumVariance << " is the variance." << std::endl;
    std::cout << stdDeviation << " is the standard deviation.\n" << std::endl;
}

void findDataPoint(const std::vector<DataPoint>& data) { // Finds specific data value or value of specific date.
    std::string userInp {};
    std::cout << "Find specific value (eg. 25.5) or date (eg. 2025/06/31). If finished, type \"done\": \n";

    while(true) { // Loops until valid formatted input, then checks vector for match.
        bool matchFound = false;
        std::cout << "> ";
        std::getline(std::cin, userInp);
        if (userInp == "done") break;
        if (!isDate(userInp) && !isTempValue(userInp)) { // Checks for valid input.
            std::cout << "Invalid input.\n";
            continue;
        }
        for (const DataPoint& d: data) { // Loops through vector and prints matches.
            if (isDate(userInp)) {
                char time[CHAR_ARRAY_SIZE];
                strftime(time, sizeof(time), "%Y/%m/%d", &d.datetime);
                if (std::string(time) == userInp) {
                    std::cout << "MATCH! " << time << " " << d.tempValue << std::endl;
                    matchFound = true;
                }
            } else if (isTempValue(userInp)) {
                float userSearch {};
                userSearch = std::stof(userInp);
                if (d.tempValue == userSearch) {
                    char time[CHAR_ARRAY_SIZE];
                    strftime(time, sizeof(time), "%a%e %b %H:%M:%S", &d.datetime);
                    std::cout << "MATCH! " << time << " " << d.tempValue << std::endl;
                    matchFound = true;
                }
            }
        } 
        if (!matchFound) {
            std::cout << "No match.\n";
        }
    }
}

void sortData(std::vector<DataPoint>& data) { // Sorts vector by value or by date.
    std::cout << "Sort data by [v]alue or by [d]ate. If finished, type \"done\": \n";
    std::string userInp {};

    while (true) { // Loops until valid input is given.
        std::cout << "> ";
        std::getline(std::cin, userInp);
        if (userInp == "v") {
            std::sort(data.begin(), data.end(), [](const DataPoint& a, const DataPoint& b) {return a.tempValue < b.tempValue;});
            break;
        } else if (userInp == "d") {
            // SORT BY DATE
            std::sort(data.begin(), data.end(), [](const DataPoint& a, const DataPoint& b) {
                tm tmConvertA = a.datetime;
                tm tmConvertB = b.datetime;

                time_t time_a = std::mktime(&tmConvertA);
                time_t time_b = std::mktime(&tmConvertB);

                return time_a < time_b;
            });
            //We don't mess with this line
            break;
        } else if (userInp == "done") {
            break;
        } else {
            std::cout << "Invalid input.\n";
        }
    }
}

void printData(const std::vector<DataPoint>& data) {
    int count = 1;

    std::cout << "\n*********************************************" << std::endl;
    std::cout << "*********** CURRENT VECTOR DATA *************" << std::endl;
    std::cout << "*********************************************" << std::endl;

    std::cout << std::endl;
    for (const DataPoint& d : data) { // Print current elements in vector.
        char time[CHAR_ARRAY_SIZE];
        strftime(time, sizeof(time), "%a%e %b %H:%M:%S", &d.datetime);
        std::cout << "#" << count++ << ": " << d.tempValue << " - " << time << std::endl;
    }
    std::cout << "\n";
}



/***********************************************************
************************ ESSENTIALS ************************
***********************************************************/

int menu() { // Display menu and validate input.
    int menuChoice = 0;
    std::string input;

    std::cout << "\nMENU\n"
              << "1. Add new values\n"
              << "2. Display statistics\n"
              << "3. Display graph\n"
              << "4. Display values sorted\n"
              << "5. Find value\n"
              << "6. Simulate values\n"
              << "7. Quit";

    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, input);

        try {
            menuChoice = std::stoi(input);
            if (menuChoice >= MIN_MENU_OPTION && menuChoice <= MAX_MENU_OPTION) {
                return menuChoice;
            }
            std::cout << "Please enter a number between 1-7.\n";
        } catch (...) {
            std::cout << "Please enter a valid number.\n";
        }
    }
}

bool action(int chosenAction, std::vector<DataPoint>& data) {
    switch (chosenAction) {
        case add: addValues(data); break;
        case disp: calcStats(data); break;
        case graph: break; // WORK IN PROGRESS
        case dispSorted: sortData(data); break;
        case find: findDataPoint(data); break;
        case simulate: break; // WORK IN PROGRESS
        case quit: return true;
    }
    return false;
}

/*****************************************************
************************ MAIN ************************
/****************************************************/

int main() {
    std::vector<DataPoint> temperatureData;
    bool shouldQuit = false;

    while (!shouldQuit) {
        int choice = menu();
        shouldQuit = action(choice, temperatureData);
    }
    std::cout << "Bye!\n";
    return 0;
}