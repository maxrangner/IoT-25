#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "definitions.hpp"

struct tm getTime();
bool isTempValue(const std::string& userInp);
bool isDate(const std::string& userInp);
void printData(const std::vector<DataPoint>& data);
void addValues(std::vector<DataPoint>& data);
void calcStats(const std::vector<DataPoint>& data);
void findDataPoint(const std::vector<DataPoint>& data);
void sortData(const std::vector<DataPoint>& data);

#endif