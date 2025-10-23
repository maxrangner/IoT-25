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