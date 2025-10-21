#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <ctime>
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

bool readFromFile(std::map<time_t,std::vector<DataPoint>> database) {
    std::ifstream inFile("data.txt");
    if (!inFile) return false;

    std::string newLine;
    while(std::getline(inFile, newLine)) {
        std::cout << newLine << std::endl;

        std::stringstream ss(newLine);
        std::string extractedValue;
        int indexCount {};
        time_t timestamp {};
        int id {};
        int type {};
        float value {};
        bool active {};
        bool triggered {};
        DataPoint newDataPoint;
        while (std::getline(ss, extractedValue, ',')) {
            switch (indexCount) {
                case 0: {
                    timestamp = static_cast<time_t>(std::stoll(extractedValue));
                    database[timestamp];
                    break;
                }
                case 1: id = std::stoi(extractedValue); break;
                case 2: type = std::stoi(extractedValue); break;
                case 3: value = std::stof(extractedValue); break;
                case 4: active = std::stoi(extractedValue) ? true : false; break;
                case 5: triggered = std::stoi(extractedValue) ? true : false; break;
            }
            if (indexCount == 5) {
                database[timestamp].emplace_back(id, type, value, active, triggered);
                indexCount = 0;
            }
        }
    }
    inFile.close();
    return true;
}