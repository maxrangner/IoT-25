#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <map>
#include <vector>
#include <string>
// #include "SystemManager.h"
#include "definitions.h"

class SystemManager;

bool writeToFile(const std::map<time_t,std::vector<DataPoint>>& database);
bool readFromFile(SystemManager& manager);
void printDatabase(const std::map<time_t,std::vector<DataPoint>>& database);
bool isValidInput(const std::string& input, int typeSelector, float min, float max);

#endif