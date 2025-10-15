#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <cfloat>
#include "definitions.hpp"

// DATA FUNCTIONS
void addValues(std::vector<DataPoint>& data, float newVal);
void generateDataPoints(std::vector<DataPoint>& data, bool fill = false);
void printData(const std::vector<DataPoint>& data);

// CORE
void calcStats(const std::vector<DataPoint>& data);
void findData(const std::vector<DataPoint>& data);
void sortData(const std::vector<DataPoint>& data);

// TOOLS
struct tm getTime();
bool isTemperatureValue(const std::string& userInp);
bool isDate(const std::string& userInp);
bool isValidInput(const std::string& input, int typeSelector, float min = -FLT_MAX, float max = FLT_MAX);
bool isValidInput(const std::string& input, int typeSelector, const std::vector<std::string>& allowedStrings);
float getRandomTemp(float min = -20.0, float max = 50.0);
struct tm getRandomTime(int timeSpan);

// UI FUNCTIONS
void uiAddValues(std::vector<DataPoint>& data);
void uiGenerateDataPoints(std::vector<DataPoint>& data);
void printData(const std::vector<DataPoint>& data, statistics& stats);

#endif
