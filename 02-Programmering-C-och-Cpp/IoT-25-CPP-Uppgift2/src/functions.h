#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <map>
#include <vector>
#include "functions.h"
#include "definitions.h"

bool writeToFile(const std::map<time_t,std::vector<DataPoint>>& database);
bool readFromFile(std::map<time_t,std::vector<DataPoint>>& database);
void printDatabase(const std::map<time_t,std::vector<DataPoint>>& database);

#endif