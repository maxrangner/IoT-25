#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>

// ************************ CONSTANTS, VARIABLES AND DATASTRUCTS ************************
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


/******************************************************
************************ TOOLS ************************
******************************************************/

struct tm getTime() {
    std::time_t timestamp = time(&timestamp);
    struct tm currentTime = *localtime(&timestamp);

    return currentTime;
}

// ************************ FUNCTIONS ************************
void addValues(std::vector<DataPoint>& data) {
    std::string userInp {};
    std::cout << "Add new value. If finished, type \"done\": \n\n";

    while(true) {
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
    int loop = 1;
    std::cout << std::endl;
    for (DataPoint measurement : data) {
        char time[50];
        strftime(time, 50, "%a%e %b %H:%M:%S", &measurement.datetime);
        std::cout << loop++ << ": " << measurement.tempValue << " - " << time << std::endl;
    }
    std::cout << "\n\n";
}

void displayValues(const std::vector<DataPoint>& data) {
    int numDataPoints {};
    double sum {};
    double average {};
    double sumVariance {};
    float variance {};
    float stdDeviation {};
    int loop = 1;
    float minVal = data[0].tempValue;
    float maxVal = data[0].tempValue;

    // Print registered data points with timestamps, count number of datapoints registered and average.
    std::cout << std::endl;
    for (DataPoint d : data) {
        char time[50];
        strftime(time, 50, "%a%e %b %H:%M:%S", &d.datetime);
        std::cout << loop++ << ": " << d.tempValue << " - " << time << "\n";

        numDataPoints++;
        sum += d.tempValue;
    }

    average = sum / numDataPoints;

    // Calculate statistics
    for (DataPoint d : data) {
        sumVariance += (d.tempValue - average) * (d.tempValue - average);
        if (d.tempValue < minVal) {
            minVal = d.tempValue;
        }
        if (d.tempValue > maxVal) {
            maxVal = d.tempValue;
        } 
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

// ************************ ESSENTIALS ************************
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
        case disp: displayValues(data); break;
        case find: break; // TEMP
        case dispSorted: break; // TEMP
        case quit: return true;
    }
    return false;
}

// ************************ MAIN ************************
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