#include <iostream>
#include <random>
#include <cfloat>
#include <ctime>
#include "functions.h"
#include "definitions.h"

std::string toLowerCase(std::string str) {
    for (char& c : str) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return str;
}

float getRandomNumber(float min, float max) {
    static std::random_device randDevice;
    static std::mt19937 gen(randDevice());
    std::uniform_real_distribution<float> distrib(min, max);
    float returnVal = distrib(gen);

    return std::round(returnVal * 100.0f) / 100.0f;

}

std::string getLine() {
    std::string userInp;
    std::cout << "> ";
    std::getline(std::cin, userInp);
    userInp = toLowerCase(userInp);
    return userInp;
}

std::string readTime(std::time_t timestamp) {
    struct tm currentTime = *localtime(&timestamp);
    char time[CHAR_ARRAY_SIZE];
    strftime(time, sizeof(time), "%a%e %b %H:%M:%S", &currentTime);
    return time;
}

std::string readDate(std::time_t timestamp) {
    struct tm currentTime = *localtime(&timestamp);
    char time[CHAR_ARRAY_SIZE];
    strftime(time, sizeof(time), "%Y/%m/%d", &currentTime);
    return time;
}

std::string convertSensorType(int type) {
    switch (type)
    {
    case 0: return "noType";
    case 1: return "temperatureSensor";
    case 2: return "humiditySensor";
    case 3: return "lightSensor";
    case 4: return "movementSensor";
    
    default:
        return "noType";
    }
}

bool isValidChoice(const std::string& inpStr, const std::vector<std::string>& valids) {
    for (const std::string& s : valids) {
        if (inpStr == s) return true;
    }
    return false;
}

bool isValidNum(const std::string& inpStr, float min, float max) {
    try {
        float convertedVal = std::stof(inpStr);
        if (convertedVal >= min && convertedVal <= max) return true;
        return false;
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