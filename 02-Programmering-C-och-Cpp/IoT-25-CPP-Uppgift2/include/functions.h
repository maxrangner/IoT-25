#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <ctime>
#include <cfloat>
#include <vector>
#include "definitions.h"

float getRandomNumber(float min = RANDOM_MIN, float max = RANDOM_MAX);
std::string convertSensorType(int type);
std::string readTime(std::time_t);
std::string readDate(std::time_t timestamp);
std::string toLowerCase(std::string str);
std::string getLine();

bool isValidNum(const std::string& inpStr, float min = -FLT_MAX, float max = FLT_MAX);
bool isValidChoice(const std::string& inpStr, const std::vector<std::string>& valids);
bool isDate(const std::string& userInp);


#endif