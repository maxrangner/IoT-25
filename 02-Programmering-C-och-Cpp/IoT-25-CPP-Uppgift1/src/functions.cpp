#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <random>
#include "functions.h"

/*************************************************************
*********************** DATA FUNCTIONS ***********************
/************************************************************/

void addValue(std::vector<DataPoint>& data, float newVal) {
    DataPoint newDataPoint;
    newDataPoint.temperatureValue = newVal;
    newDataPoint.datetime = getTime();
    constrainVectorSize(data);
    data.push_back(newDataPoint);
}

void generateDataPoints(std::vector<DataPoint>& data) {
    DataPoint newDataPoint;
    constrainVectorSize(data);
    newDataPoint.temperatureValue = getRandomTemp(15,25);
    newDataPoint.datetime = getRandomTime(MONTH_IN_SEC);
    data.push_back(newDataPoint);
}

void generateDataPoints(std::vector<DataPoint>& data, int numDatapoints) {
    DataPoint newDataPoint;
    if (numDatapoints > 1) {
        data.clear();
    }
    for (int i = 0; i < numDatapoints; i++) {
        constrainVectorSize(data);
        newDataPoint.temperatureValue = getRandomTemp(15,25);
        newDataPoint.datetime = getRandomTime(MONTH_IN_SEC);
        data.push_back(newDataPoint);
    }
}

/******************************************************
************************ CORE *************************
******************************************************/

statistics calcStats(const std::vector<DataPoint>& data) {
    statistics outputStats;
    if (data.empty()) return outputStats;
    else outputStats.empty = false;

    outputStats.numDataPoints = data.size();
    outputStats.minVal = data[0].temperatureValue;
    outputStats.maxVal = data[0].temperatureValue;

    for (const DataPoint& d : data) {
        outputStats.sum += d.temperatureValue;
        if (d.temperatureValue < outputStats.minVal) {
            outputStats.minVal = d.temperatureValue;
        }
        if (d.temperatureValue > outputStats.maxVal) {
            outputStats.maxVal = d.temperatureValue;
        } 
    }

    outputStats.average = outputStats.sum / outputStats.numDataPoints;

    for (const DataPoint& d : data) {
        outputStats.variance += (d.temperatureValue - outputStats.average) * (d.temperatureValue - outputStats.average);
    }

    outputStats.variance = outputStats.variance / outputStats.numDataPoints;
    outputStats.stdDeviation = std::sqrt(outputStats.variance);

    return outputStats;
}

std::vector<DataPoint> findData(const std::vector<DataPoint>& data, std::string userInp) {
    std::vector<DataPoint> results;

    for (const DataPoint& d: data) {
        if (isDate(userInp)) {
            char time[CHAR_ARRAY_SIZE];
            strftime(time, sizeof(time), "%Y/%m/%d", &d.datetime);
            if (std::string(time) == userInp) {
                results.push_back(d);
            }
        } else if (isTemperatureValue(userInp)) {
            float userSearch {};
            userSearch = std::stof(userInp);
            if (d.temperatureValue == userSearch) {
                results.push_back(d);
            }
        }
    }
    return results;
}

std::vector<DataPoint> sortData(const std::vector<DataPoint>& data, std::string userInp) {
    std::vector<DataPoint> sortedData = data;

    if (userInp == "v" || userInp == "V") {
        std::sort(sortedData.begin(), sortedData.end(), [](const DataPoint& a, const DataPoint& b) {return a.temperatureValue < b.temperatureValue;});
        return sortedData;
    } else if (userInp == "d" || userInp == "D") {
        std::sort(sortedData.begin(), sortedData.end(), [](const DataPoint& a, const DataPoint& b) {
            tm tmConvertA = a.datetime;
            tm tmConvertB = b.datetime;

            time_t time_a = std::mktime(&tmConvertA);
            time_t time_b = std::mktime(&tmConvertB);

            return time_a < time_b;
        });
        return sortedData;
    }
}

/******************************************************
************************ TOOLS ************************
******************************************************/

void constrainVectorSize(std::vector<DataPoint>& data) {
    if (data.size() >= MAX_DATA_POINTS) {
        data.erase(data.begin());
    }
}

struct tm getTime() {
    std::time_t timestamp = std::time(nullptr);
    struct tm currentTime = *localtime(&timestamp);

    return currentTime;
}

float getRandomTemp(float min, float max) {
    static std::random_device randDevice;
    static std::mt19937 gen(randDevice());
    std::uniform_real_distribution<float> distrib(min, max);
    float returnVal = distrib(gen);

    return std::round(returnVal * 100.0f) / 100.0f;
}

struct tm getRandomTime(int timeSpan) {
    static std::random_device randDevice;
    static std::mt19937 gen(randDevice());

    time_t currentTime = std::time(nullptr);
    time_t minTime = currentTime - timeSpan; 
    std::uniform_int_distribution<time_t> distrib(minTime, currentTime);
    time_t randomTimeT = distrib(gen);
    struct tm output = *localtime(&randomTimeT);

    return output;
}

/******************************************************
********************* VALIDATORS **********************
******************************************************/

bool isTemperatureValue(const std::string& userInp) {
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

bool isValidInput(const std::string& input, int typeSelector, float min, float max) {
    switch (typeSelector) {
        case wholeNum: {
            try {
                int inputVal = std::stoi(input);
                if (inputVal >= min && inputVal <= max) return true;
                std::cout << "Please enter a number between " << min << " and " << max << "\n";
            } catch (...) {
                std::cout << "Please enter a valid number.\n";
            }
            break;
        }
        case decimalNum: {
            try {
                float inputVal = std::stof(input);
                if (inputVal >= min && inputVal <= max) return true;
                std::cout << "Please enter a number between " << min << " and " << max << "\n";
            } catch (...) {
                std::cout << "Please enter a valid number.\n";
            }
            break;
        }
    };

    return false;
}

bool isValidInput(const std::string& input, int typeSelector, const std::vector<std::string>& allowedStrings) {
    int numAllowed = 0;
    for (const auto& s : allowedStrings) {
        numAllowed++;
        if (input == s) return true;
    }
    std::string msg = "Please enter "; 
    for (int i = 0; i < numAllowed; i++) {
        msg += "\"" + allowedStrings[i] + "\"";
        if (i < (numAllowed -2)) msg += ", ";
        else if (i < (numAllowed -1)) msg += " or ";
        else msg += ".\n";
    }
    std::cout << msg;

    return false;
}

/*************************************************************
************************ UI FUNCTIONS ************************
/************************************************************/

void uiAddValues(std::vector<DataPoint>& data) {
    std::string userInp {};
    std::cout << "Add new value. If finished, type \"done\": \n";

    while(true) {
        std::cout << "> ";
        std::getline(std::cin, userInp);
        if (userInp == "done") break;
        if (isValidInput(userInp, decimalNum, -100, 100)) {
            float convertedInput = std::stof(userInp);
            addValue(data, convertedInput);
            std::cout << "Value added!\n";
        }
    }
    printData(data);
}

void uiDisplayStats(const std::vector<DataPoint>& data) {
    if (data.empty()) { std::cout << "No data saved.\n"; return; }

    statistics newStats = calcStats(data);
    printData(data, newStats);
}

void uiDisplayGraph(const std::vector<DataPoint>& data) {
    // NOT YET IMPLEMENTED.
    std::cout << "NOT YET IMPLEMENTED." << std::endl;
}

void uiDisplaySorted(const std::vector<DataPoint>& data) {
    if (data.empty()) { std::cout << "No data saved.\n"; return; }

    std::string userInp {};
    std::cout << "\nSort data by [v]alue or by [d]ate. To cancel, type \"done\": \n";
    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, userInp);
        
        if (isValidInput(userInp, text, {"v", "V", "d", "D", "done"})) {
            if (userInp == "done") break;
            std::vector<DataPoint> sortedData;
            sortedData = sortData(data, userInp);
            printData(sortedData);
            return;
        }
    }
}

void uiFindData(const std::vector<DataPoint>& data) {
    if (data.empty()) { std::cout << "No data saved.\n"; return; }

    std::string userInp {};
    std::vector<DataPoint> searchResult;
    std::cout << "Find specific value (eg. 25.5) or date (eg. 2025/06/31). If finished, type \"done\": \n";

    while(true) {
        std::cout << "> ";
        std::getline(std::cin, userInp);
        if (userInp == "done") break;
        if (isDate(userInp) || isTemperatureValue(userInp)) {
            searchResult = findData(data, userInp);
            if (searchResult.empty()) std::cout << "No match.\n";
            else {
                printData(searchResult);
            }
        } else {
            std::cout << "Invalid input.\n";
            continue;
        }
    }    
}

void uiGenerateDataPoints(std::vector<DataPoint>& data) {
    std::string userInp {};
    std::cout << "Generate random data points. [S]ingle new value or [f]ill database: \n";

    while(true) {
        std::cout << "> ";
        std::getline(std::cin, userInp);
        if (isValidInput(userInp, text, {"S", "s", "F", "f"})) {
            if (userInp == "f" || userInp == "F") {
                generateDataPoints(data, MAX_DATA_POINTS);
                std::cout << MAX_DATA_POINTS << " random data points added to database.\n";
            } else if (userInp == "s" || userInp == "S") {
                generateDataPoints(data);
                std::cout << "Single random data point added.\n";
            }
            printData(data);
            return;
        }
    }
}

void printData(const std::vector<DataPoint>& data) {
    if (data.empty()) { std::cout << "No data saved.\n"; return; }
    int count = 1;

    std::cout << "\n*********************************************" << std::endl;
    std::cout << "*********** CURRENT VECTOR DATA *************" << std::endl;
    std::cout << "*********************************************" << std::endl;

    std::cout << std::endl;
    for (const DataPoint& d : data) {
        char time[CHAR_ARRAY_SIZE];
        strftime(time, sizeof(time), "%a%e %b %H:%M:%S", &d.datetime);
        std::cout << "#" << count++ << ": " << std::fixed << std::setprecision(2) << d.temperatureValue << " - " << time << std::endl;
    }
    std::cout << "\n";
}

void printData(const std::vector<DataPoint>& data, statistics& stats) {
    int spacing = 30;

    printData(data);
    std::cout << std::left << std::setw(spacing) << "Sum: " << stats.sum << std::endl
              << std::left << std::setw(spacing) << "Average:" << stats.average << std::endl
              << std::left << std::setw(spacing) << "Min:" << stats.minVal << std::endl
              << std::left << std::setw(spacing) << "Max:" << stats.maxVal << std::endl
              << std::left << std::setw(spacing) << "Variance:" << stats.variance << std::endl
              << std::left << std::setw(spacing) << "Standard deviation:" << stats.stdDeviation << std::endl;
}