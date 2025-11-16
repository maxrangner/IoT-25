#pragma once
#include <string>
#include <vector>
#include <ctime>
#include "definitions.h"

std::string makeLower(std::string input);
std::string convertFromSensorType(SensorType type);
SensorType convertToSensorType(std::string type);
float getRandomNumber(float min = -100.0, float max = 100.0);
time_t getTime();
std::string formatTime(std::time_t timestamp, bool showDate = true);
std::string formatStringColor(const Measurement& m, const Alarms& alarms);
std::string sensorTypeToString(SensorType type);
std::string trimDecimals(float value, int precision = 1);
Statistics getStatistics(std::vector<Measurement>& log);
void trimCR(std::string& s);