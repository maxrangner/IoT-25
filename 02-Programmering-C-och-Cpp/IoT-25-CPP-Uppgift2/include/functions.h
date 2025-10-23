#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <ctime>
#include "definitions.h"

std::string toLowerCase(std::string str);
float getRandomNumber(float min = RANDOM_MIN, float max = RANDOM_MAX);
std::string getLine();
std::string readTime(std::time_t);
std::string convertSensorType(int type);

#endif