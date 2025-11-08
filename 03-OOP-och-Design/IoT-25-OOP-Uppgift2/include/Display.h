#pragma once
#include <iostream>
#include <mutex>

class Display {
    std::mutex logMutex;
public:
    void printMenu() const;
    void printHeader(const std::string& text) const;
    void printMessage(const std::string& text, bool lineBreak = true) const;
    void clear();
};