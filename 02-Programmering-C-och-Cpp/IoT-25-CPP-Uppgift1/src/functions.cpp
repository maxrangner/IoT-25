#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <random>
#include "functions.hpp"

/******************************************************
************************ TOOLS ************************
******************************************************/

struct tm getTime() { // Gets current time from <ctime> module. Returns tm struct.
    std::time_t timestamp = std::time(nullptr);
    struct tm currentTime = *localtime(&timestamp);

    return currentTime;
}

bool isTemperatureValue(const std::string& userInp) { // Checks if string is a valid temperature value. Returns true/false.
    try {
        std::stof(userInp);
        return true;
    } catch (...) {
        return false;
    }
}

bool isDate(const std::string& userInp) { // Checks if string is a valid date (xxxx/xx/xx). Returns true/false.
    if (userInp.length() != 10) return false;
    if (userInp.at(4) != '/' || userInp.at(7) != '/') return false;
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7 && !std::isdigit(userInp[i])) return false;
    }

    return true;
}

bool isValidInput(const std::string& input, int typeSelector, float min, float max) { // Validates input based on typeSelector enum.
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

void generateData(std::vector<DataPoint>& data) {
    DataPoint newDataPoint;
    data.clear();
    for (int i = 0; i < MAX_DATA_POINTS; i++) {
        newDataPoint.temperatureValue = getRandomTemp(15,25);
        newDataPoint.datetime = getRandomTime(MONTH_IN_SEC);
        data.push_back(newDataPoint);
    }
    printData(data);
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

        if (isValidInput(userInp, decimalNum, -100, 100)) {
            newDataPoint.temperatureValue = std::stof(userInp);
            newDataPoint.datetime = getTime();
            if (data.size() >= MAX_DATA_POINTS) { // Checks if vector is too big, and limits it to MAX_DATA_POINTS.
                data.erase(data.begin());
            }
            data.push_back(newDataPoint);
        }
    }
    printData(data);
}

void calcStats(const std::vector<DataPoint>& data) { // Calculates and displays statistics based on data in vector.
    if (data.empty()) { std::cout << "No data saved.\n"; return; }
    statistics newStats;
    newStats.numDataPoints = data.size();
    newStats.minVal = data[0].temperatureValue;
    newStats.maxVal = data[0].temperatureValue;

    for (const DataPoint& d : data) { // Calculates sum and min/max values.
        newStats.sum += d.temperatureValue;
        if (d.temperatureValue < newStats.minVal) {
            newStats.minVal = d.temperatureValue;
        }
        if (d.temperatureValue > newStats.maxVal) {
            newStats.maxVal = d.temperatureValue;
        } 
    }

    newStats.average = newStats.sum / newStats.numDataPoints;

    for (const DataPoint& d : data) {
        newStats.variance += (d.temperatureValue - newStats.average) * (d.temperatureValue - newStats.average);
    }

    newStats.variance = newStats.variance / newStats.numDataPoints;
    newStats.stdDeviation = std::sqrt(newStats.variance);

    printData(data, newStats);
}

void findDataPoint(const std::vector<DataPoint>& data) { // Finds specific data value or value of specific date.
    if (data.empty()) { std::cout << "No data saved.\n"; return; }
    std::string userInp {};
    std::cout << "Find specific value (eg. 25.5) or date (eg. 2025/06/31). If finished, type \"done\": \n";

    while(true) { // Loops until valid formatted input, then checks vector for match.
        bool matchFound = false;
        std::cout << "> ";
        std::getline(std::cin, userInp);
        if (userInp == "done") break;
        if (!isDate(userInp) && !isTemperatureValue(userInp)) { // Checks for valid input.
            std::cout << "Invalid input.\n";
            continue;
        }
        for (const DataPoint& d: data) { // Loops through vector and prints matches.
            if (isDate(userInp)) {
                char time[CHAR_ARRAY_SIZE];
                strftime(time, sizeof(time), "%Y/%m/%d", &d.datetime);
                if (std::string(time) == userInp) {
                    std::cout << "MATCH! " << time << " " << d.temperatureValue << std::endl;
                    matchFound = true;
                }
            } else if (isTemperatureValue(userInp)) {
                float userSearch {};
                userSearch = std::stof(userInp);
                if (d.temperatureValue == userSearch) {
                    char time[CHAR_ARRAY_SIZE];
                    strftime(time, sizeof(time), "%a%e %b %H:%M:%S", &d.datetime);
                    std::cout << "MATCH! " << time << " " << d.temperatureValue << std::endl;
                    matchFound = true;
                }
            }
        } 
        if (!matchFound) {
            std::cout << "No match.\n";
        }
    }
}

void sortData(const std::vector<DataPoint>& data) { // Sorts vector by value or by date.
    if (data.empty()) { std::cout << "No data saved.\n"; return; }
    std::cout << "\nSort data by [v]alue or by [d]ate. If finished, type \"done\": \n";
    std::string userInp {};

    std::vector<DataPoint> sortedData = data;

    while (true) { // Loops until valid input is given.
        std::cout << "> ";
        std::getline(std::cin, userInp);
        
        if (isValidInput(userInp, text, {"v", "d", "done"})) {
            if (userInp == "v") { // Sort by value
                std::sort(sortedData.begin(), sortedData.end(), [](const DataPoint& a, const DataPoint& b) {return a.temperatureValue < b.temperatureValue;});
                break;
            } else if (userInp == "d") { // Sort by date
                std::sort(sortedData.begin(), sortedData.end(), [](const DataPoint& a, const DataPoint& b) {
                    tm tmConvertA = a.datetime;
                    tm tmConvertB = b.datetime;

                    time_t time_a = std::mktime(&tmConvertA);
                    time_t time_b = std::mktime(&tmConvertB);

                    return time_a < time_b;
                });
                break;
            } else if (userInp == "done") {
                break;
            }
        }
    }

    printData(sortedData);
}

void printData(const std::vector<DataPoint>& data) {
    if (data.empty()) { std::cout << "No data saved.\n"; return; }
    int count = 1;

    std::cout << "\n*********************************************" << std::endl;
    std::cout << "*********** CURRENT VECTOR DATA *************" << std::endl;
    std::cout << "*********************************************" << std::endl;

    std::cout << std::endl;
    for (const DataPoint& d : data) { // Print current elements in vector.
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
