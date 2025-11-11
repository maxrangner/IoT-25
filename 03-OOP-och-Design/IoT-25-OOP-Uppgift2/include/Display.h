#pragma once
#include <iostream>
#include <mutex>
#include "utils.h"

class Display {
    std::mutex logMutex;
public:
    void printMenu() const;
    void printHeader(const std::string& text) const;
    void printMessage(const std::string& text, bool lineBreak = true) const;
    void printMeasurement(const Measurement measurment) const;
    void drawGraph(const std::map<time_t, std::vector<Measurement>>& measurments) const;
    void clear();
};