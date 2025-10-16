#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <cfloat>
#include "definitions.h"

// DATA FUNCTIONS
void addValue(std::vector<DataPoint>& data, float newVal);
void generateDataPoints(std::vector<DataPoint>& data);
void generateDataPoints(std::vector<DataPoint>& data, int numDatapoints);

// CORE
statistics calcStats(const std::vector<DataPoint>& data);
std::vector<DataPoint> findData(const std::vector<DataPoint>& data, std::string userInp);
std::vector<DataPoint> sortData(const std::vector<DataPoint>& data, std::string userInp);

// TOOLS
void constrainVectorSize(std::vector<DataPoint>& data);
struct tm getTime();
float getRandomTemp(float min = -20.0, float max = 50.0);
struct tm getRandomTime(int timeSpan);

// VALIDATORS
bool isTemperatureValue(const std::string& userInp);
bool isDate(const std::string& userInp);
bool isValidInput(const std::string& input, int typeSelector, float min = -FLT_MAX, float max = FLT_MAX);
bool isValidInput(const std::string& input, int typeSelector, const std::vector<std::string>& allowedStrings);

// UI FUNCTIONS
void uiAddValues(std::vector<DataPoint>& data);
void uiDisplayStats(const std::vector<DataPoint>& data);
void uiDisplayGraph(const std::vector<DataPoint>& data); // NOT YET IMPLEMENTED
void uiDisplaySorted(const std::vector<DataPoint>& data);
void uiFindData(const std::vector<DataPoint>& data);
void uiGenerateDataPoints(std::vector<DataPoint>& data);
void printData(const std::vector<DataPoint>& data);
void printData(const std::vector<DataPoint>& data, statistics& stats);

#endif
