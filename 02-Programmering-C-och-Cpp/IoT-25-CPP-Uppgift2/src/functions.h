#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <map>
#include <vector>
#include <string>
#include "functions.h"
#include "definitions.h"

bool writeToFile(const std::map<time_t,std::vector<DataPoint>>& database);
bool readFromFile(std::map<time_t,std::vector<DataPoint>>& database);
void printDatabase(const std::map<time_t,std::vector<DataPoint>>& database);
bool isValidInput(const std::string& input, int typeSelector, float min, float max);

#endif