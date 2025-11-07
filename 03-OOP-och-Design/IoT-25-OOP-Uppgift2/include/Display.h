#pragma once
#include <iostream>

class Display {
public:
    void printMenu() const;
    void printHeader(const std::string& text) const;
    void printMessage(const std::string& text, bool lineBreak = true) const;
    void clear();
};