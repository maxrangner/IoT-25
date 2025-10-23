#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <ctime>
#include <cfloat>
#include <vector>
#include "definitions.h"

std::string toLowerCase(std::string str);
float getRandomNumber(float min = RANDOM_MIN, float max = RANDOM_MAX);
std::string getLine();
std::string readTime(std::time_t);
std::string convertSensorType(int type);
bool isValidNum(const std::string& inpStr, float min = -FLT_MAX, float max = FLT_MAX);
bool isValidChoice(const std::string& inpStr, const std::vector<std::string>& valids);
bool isDate(const std::string& userInp);
std::string readDate(std::time_t timestamp);

#endif