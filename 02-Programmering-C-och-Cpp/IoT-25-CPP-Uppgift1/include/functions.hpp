#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <cfloat>
#include "definitions.hpp"

struct tm getTime();
bool isTemperatureValue(const std::string& userInp);
bool isDate(const std::string& userInp);
void printData(const std::vector<DataPoint>& data);
void printData(const std::vector<DataPoint>& data, statistics& stats);
bool isValidInput(const std::string& input, int typeSelector, float min = -FLT_MAX, float max = FLT_MAX);
bool isValidInput(const std::string& input, int typeSelector, const std::vector<std::string>& allowedStrings);
void addValues(std::vector<DataPoint>& data);
void calcStats(const std::vector<DataPoint>& data);
void findDataPoint(const std::vector<DataPoint>& data);
void sortData(const std::vector<DataPoint>& data);
float getRandomTemp(float min = -20.0, float max = 50.0);
struct tm getRandomTime(int timeSpan);

void generateData(std::vector<DataPoint>& data);

#endif
