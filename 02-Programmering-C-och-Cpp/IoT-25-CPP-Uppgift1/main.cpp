#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <cctype>

/*************************************************************************************
************************ CONSTANTS, VARIABLES AND DATASTRUCTS ************************
*************************************************************************************/

enum MenuSelection {
    add = 1, // 1.
    disp, // 2.
    find, // 3.
    dispSorted, // 4.
    quit // 5.
};

struct DataPoint {
    float tempValue;
    struct tm datetime;
};

constexpr int MIN_MENU_OPTION = 1;
constexpr int MAX_MENU_OPTION = 5;
constexpr int MAX_DATA_POINTS = 5;
constexpr int CHAR_ARRAY_SIZE = 50;


/******************************************************
************************ TOOLS ************************
******************************************************/

struct tm getTime() {
    std::time_t timestamp = time(nullptr);
    struct tm currentTime = *localtime(&timestamp);

    return currentTime;
}

bool isTempValue(const std::string& userInp) {
    try {
        std::stof(userInp);
        return true;
    } catch (...) {
        return false;
    }
}

bool isDate(const std::string& userInp) {
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

void addValues(std::vector<DataPoint>& data) {
    std::string userInp {};
    std::cout << "Add new value. If finished, type \"done\": \n";

    while(true) {
        std::cout << "> ";
        std::getline(std::cin, userInp);
        if (userInp == "done") break;
        DataPoint newDataPoint;

        try {
            newDataPoint.tempValue = std::stof(userInp);
        } catch (...) {
            std::cout << "Please enter a valid number.\n";
            continue;
        }
        
        newDataPoint.datetime = getTime();

        if (data.size() >= MAX_DATA_POINTS) {
            data.erase(data.begin());
        }
        data.push_back(newDataPoint);
    }

    // Print current list.
    int count = 1;
    std::cout << std::endl;
    for (const DataPoint& d : data) {
        char time[CHAR_ARRAY_SIZE];
        strftime(time, sizeof(time), "%a%e %b %H:%M:%S", &d.datetime);
        std::cout << count++ << ": " << d.tempValue << " - " << time << std::endl;
    }
    std::cout << "\n\n";
}

void calcStats(const std::vector<DataPoint>& data) {
    int numDataPoints = data.size();
    double sum {};
    double average {};
    double sumVariance {};
    float variance {};
    float stdDeviation {};
    int count = 1;
    float minVal = data[0].tempValue;
    float maxVal = data[0].tempValue;

    // Print registered data points with timestamps, count number of datapoints registered and average.
    std::cout << std::endl;
    for (const DataPoint& d : data) {
        char time[CHAR_ARRAY_SIZE];
        strftime(time, sizeof(time), "%a%e %b %H:%M:%S", &d.datetime);
        std::cout << count++ << ": " << d.tempValue << " - " << time << "\n";
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

void findDataPoint(const std::vector<DataPoint>& data) {
    std::string userInp {};
    std::cout << "Find specific value (eg. 25.5) or date (eg. 2025/06/31). If finished, type \"done\": \n";

    while(true) {
        bool matchFound = false;
        std::cout << "> ";
        std::getline(std::cin, userInp);
        if (userInp == "done") break;
        if (!isDate(userInp) && !isTempValue(userInp)) {
            std::cout << "Invalid input.\n";
            continue;
        }
        for (const DataPoint& d: data) {
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

void sortData(const std::vector<DataPoint>& data) {
    // SORT FUNCTION IS WORK IN PROGRESS
}

/***********************************************************
************************ ESSENTIALS ************************
***********************************************************/

int menu() {
    int menuChoice {};
    std::string input;

    std::cout << "MENU\n"
              << "1. Add new values\n"
              << "2. Display statistics\n"
              << "3. Find value\n"
              << "4. Display values sorted\n"
              << "5. Quit\n";

    while (true) {
        std::cout << "\nOption: ";
        std::getline(std::cin, input);

        try {
            menuChoice = std::stoi(input);
            if (menuChoice >= MIN_MENU_OPTION && menuChoice <= MAX_MENU_OPTION) {
                return menuChoice;
            }
            std::cout << "Please enter a number between 1-5.\n";
        } catch (...) {
            std::cout << "Please enter a valid number.\n";
        }
    }
}

bool action(int chosenAction, std::vector<DataPoint>& data) {
    switch (chosenAction) {
        case add: addValues(data); break;
        case disp: calcStats(data); break;
        case find: findDataPoint(data); break;
        case dispSorted: sortData(data); break; // TEMP
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