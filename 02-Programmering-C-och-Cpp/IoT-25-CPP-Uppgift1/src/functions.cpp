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
    constrainVectorSize(data); // This function deletes the oldest entry of the vector if it has already reached MAX_DATA_POINTS.
    data.push_back(newDataPoint); // This adds the new data point to the newest position of the vector.
}

void generateDataPoints(std::vector<DataPoint>& data) {
    DataPoint newDataPoint;
    constrainVectorSize(data);
    newDataPoint.temperatureValue = getRandomTemp(15,25); // Gets a random float, in the span of 15-25.
    newDataPoint.datetime = getRandomTime(MONTH_IN_SEC); // Get a random struct tm, in the span one month back to current time.
    data.push_back(newDataPoint);
}

void generateDataPoints(std::vector<DataPoint>& data, int numDatapoints) { // Overload function. If provided an int it feeds as many random DataPoints to the vector.
    DataPoint newDataPoint;
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

Statistics calcStats(const std::vector<DataPoint>& data) {
    Statistics outputStats; // A Statistics struct to be returned and later printed by an overload version of printData().
    if (data.empty()) return outputStats;

    outputStats.numDataPoints = data.size();
    outputStats.minVal = data[0].temperatureValue; // Sets an initial min value to compare against in the upcoming loop.
    outputStats.maxVal = data[0].temperatureValue; // Sets an initial max value to compare against in the upcoming loop.

    for (const DataPoint& d : data) {
        outputStats.sum += d.temperatureValue;
        if (d.temperatureValue < outputStats.minVal) {
            outputStats.minVal = d.temperatureValue;
        }
        if (d.temperatureValue > outputStats.maxVal) {
            outputStats.maxVal = d.temperatureValue;
        } 
    }

    // Various calculations. Some using previous ones to build upon.
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

    for (const DataPoint& d: data) { // Goes through the different DataPoints in data. Every loop the current DataPoint is given the variable 'd'.
        if (isDate(userInp)) { // If the input is cleared as a date:
            char time[CHAR_ARRAY_SIZE]; // Creates a character array to be used by strftime.
            strftime(time, sizeof(time), "%Y/%m/%d", &d.datetime); // Extracts the timestamp from the current DataPoint.
            if (std::string(time) == userInp) { // Checks if user input matches the current timestamp.
                results.push_back(d); // If match: add to results vector.
            }
        } else if (isTemperatureValue(userInp)) {
            float userSearch {};
            userSearch = std::stof(userInp); // Casts the user input string as a float.
            if (d.temperatureValue == userSearch) { // Checks if it matches the current temperature value.
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
        
        std::sort(sortedData.begin(), sortedData.end(), [](const DataPoint& a, const DataPoint& b) { // This is the sort function unsing a lambda funcion to convert the struct tm timestamp to it's original long long.
            tm tmConvertA = a.datetime;
            tm tmConvertB = b.datetime;

            time_t time_a = std::mktime(&tmConvertA);
            time_t time_b = std::mktime(&tmConvertB);

            return time_a < time_b; // The two converted long longs can eaisly be compared to see which is greater.
        });
        return sortedData;
    }
    return sortedData;
}

/******************************************************
************************ TOOLS ************************
******************************************************/

void constrainVectorSize(std::vector<DataPoint>& data) {
    if (data.size() >= MAX_DATA_POINTS) { // If the vector is full: erase the oldest entry.
        data.erase(data.begin());
    }
}

struct tm getTime() {
    std::time_t timestamp = std::time(nullptr); // Get's the time in a time_t format, which is typically a long long.
    struct tm currentTime = *localtime(&timestamp); // Converts the time_t object to a struct tm which is easy to extract year, month, etc.

    return currentTime;
}

float getRandomTemp(float min, float max) {
    static std::random_device randDevice; // The seed source to be used.
    static std::mt19937 gen(randDevice()); // Pseudo-random generator
    std::uniform_real_distribution<float> distrib(min, max); // Defines the range of random float values.
    float returnVal = distrib(gen); // Uses the generator to extract a float.

    return std::round(returnVal * 100.0f) / 100.0f; // This rounds the float to two decimals.
}

struct tm getRandomTime(int timeSpan) { // Uses the same random techniques as getRandomTemp and the compare lambda in sortData. 
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

bool isDate(const std::string& userInp) { // This checks if the input string follows the format xxxx/xx/xx by counting index and checking if '/' is in the right place.
    if (userInp.length() != 10) return false;
    if (userInp.at(4) != '/' || userInp.at(7) != '/') return false;
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7 && !std::isdigit(userInp[i])) return false;
    }

    return true;
}

bool isValidInput(const std::string& input, int typeSelector, float min, float max) { // Uses try/catch to try and cast the user input to either int or float.
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

bool isValidInput(const std::string& input, int typeSelector, const std::vector<std::string>& allowedStrings) { // Overloaded version that takes a vector of strings, to check if either is present in the user input.
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
*************************************************************/

/*
These UI functions simply takes a user input and utilizes the different data, core and validator functions to provide the correct action.
*/

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

void uiDisplayData(const std::vector<DataPoint>& data) {
    if (data.empty()) { std::cout << "No data saved.\n"; return; }

    printData(data);
}

void uiDisplayStats(const std::vector<DataPoint>& data) {
    if (data.empty()) { std::cout << "No data saved.\n"; return; }

    Statistics newStats = calcStats(data);
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
            if (userInp == "done") return;
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
            else printData(searchResult);
        } else std::cout << "Invalid input.\n"; continue;
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

    std::cout << "\n*********************************************\n"
              << "************** TEMPERATURE DATA *************\n"
              << "*********************************************\n"
              << std::endl;

    for (const DataPoint& d : data) {
        char time[CHAR_ARRAY_SIZE];
        strftime(time, sizeof(time), "%a%e %b %H:%M:%S", &d.datetime);
        std::cout << "#" << count++ << ": " << std::fixed << std::setprecision(2) << d.temperatureValue << " - " << time << std::endl;
    }
    std::cout << std::endl;
}

void printData(const std::vector<DataPoint>& data, Statistics& stats) {
    int spacing = 30;

    printData(data);

    std::cout << "\n*********************************************\n"
              << "***************** STATISTICS ****************\n"
              << "*********************************************\n"
              << std::endl;

    std::cout << std::left << std::setw(spacing) << "Sum: " << stats.sum << std::endl
              << std::left << std::setw(spacing) << "Average:" << stats.average << std::endl
              << std::left << std::setw(spacing) << "Min:" << stats.minVal << std::endl
              << std::left << std::setw(spacing) << "Max:" << stats.maxVal << std::endl
              << std::left << std::setw(spacing) << "Variance:" << stats.variance << std::endl
              << std::left << std::setw(spacing) << "Standard deviation:" << stats.stdDeviation << std::endl;
}