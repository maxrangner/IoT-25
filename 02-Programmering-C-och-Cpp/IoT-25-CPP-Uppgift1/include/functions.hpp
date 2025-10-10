#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <cfloat>
#include "definitions.hpp"

struct tm getTime();
bool isTemperatureValue(const std::string& userInp);
bool isDate(const std::string& userInp);
void printData(const std::vector<DataPoint>& data);
bool isValidInput(const std::string& input, int typeSelector, float min = -FLT_MAX, float max = FLT_MAX);
void addValues(std::vector<DataPoint>& data);
void calcStats(const std::vector<DataPoint>& data);
void findDataPoint(const std::vector<DataPoint>& data);
void sortData(const std::vector<DataPoint>& data);

#endif
