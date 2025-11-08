#pragma once
#include <string>
#include <ctime>
#include "definitions.h"

std::string makeLower(std::string input);
std::string convertSensorType(SensorType type);
float getRandomNumber(float min = -100.0, float max = 100.0);
time_t getTime();
std::string readTime(std::time_t timestamp);
std::string sensorTypeToString(SensorType type);