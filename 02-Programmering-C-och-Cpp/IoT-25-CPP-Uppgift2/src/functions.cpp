#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <ctime>
#include "SystemManager.h"
#include "functions.h"
#include "definitions.h"

bool writeToFile(const std::map<time_t,std::vector<DataPoint>>& database) {
    std::ofstream outFile("data.txt");
    if (!outFile) return false;

    for (auto& pair : database) {
        outFile << pair.first << ",";
        for (DataPoint DP : pair.second) {
            outFile << DP.deviceId << ","
                    << DP.type << ","
                    << DP.value << ","
                    << DP.isActive << ","
                    << DP.isTriggered << ",";
        }
        outFile << std::endl;
    }

    outFile.close();
    return true;
}

bool readFromFile(SystemManager& manager) {
    manager.database.clear();
    
    std::ifstream inFile("data.txt");
    if (!inFile) return false;

    std::string newLine;
    while(std::getline(inFile, newLine)) {
        std::stringstream ss(newLine);
        std::string extractedValue;

        int indexCount {};
        int fieldCount {};

        time_t timestamp {};
        int id {};
        int type {};
        float value {};
        bool active {};
        bool triggered {};
        
        while (std::getline(ss, extractedValue, ',')) {
            if (extractedValue.empty()) continue;

            if (indexCount == 0) {      // första värdet
                timestamp = stoll(extractedValue);
                indexCount++;
                continue;
            }

            switch (fieldCount) {
                case 0: id = std::stoi(extractedValue); break;
                case 1: type = std::stoi(extractedValue); break;
                case 2: value = std::stof(extractedValue); break;
                case 3: active = std::stoi(extractedValue) ? true : false; break;
                case 4: triggered = std::stoi(extractedValue) ? true : false; break;
            }
            fieldCount++;
            if (fieldCount == 5) {
                if (!extractedValue.empty()) {
                    manager.database[timestamp].emplace_back(id, type, value, active, triggered);
                }
                fieldCount = 0;
            }
            indexCount++;
        }
    }
    // manager.resetSystem();
    inFile.close();
    return true;
}

void printDatabase(const std::map<time_t,std::vector<DataPoint>>& database) {
    for (auto& pair : database) {
        std::cout << "Timestamp: " << pair.first << ":\n";
        for (auto& v : pair.second) {
            std::cout << "**************\n"
                      << "deviceId: " << v.deviceId << " | "
                      << "type: " << v.type << " | "
                      << "value: " << v.value << " | "
                      << "isActive: " << v.isActive << " | "
                      << "isTriggered: " << v.isTriggered << "\n";
        }
        std::cout << std::endl;
    }
}

bool isValidInput(const std::string& input, int typeSelector, float min, float max) { // Uses try/catch to try and cast the user input to either int or float.
    switch (typeSelector) {
        case wholeNum: {
            try {
                int inputVal = std::stoi(input);
                if (inputVal >= min && inputVal <= max) return true;
                std::cout << "Please enter a number between " << static_cast<int>(min) << " and " << static_cast<int>(max) << "\n";
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