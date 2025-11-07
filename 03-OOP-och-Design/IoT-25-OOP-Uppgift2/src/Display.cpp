#include <iomanip>
// #include <cstdlib>
#include "Display.h"

void Display::printMenu() const {
    int spacing = 4;

    std::cout << "\n*--- MENU ---*\n"
              << std::left << std::setw(spacing) << "[1]    " << "Add / remove sensor\n"
              << std::left << std::setw(spacing) << "[2]    " << "Status Screen\n"
              << std::left << std::setw(spacing) << "[3]    " << "Search *** NOT IMPELEMENTED ***\n"
              << std::left << std::setw(spacing) << "[4]    " << "Settings *** NOT IMPELEMENTED ***\n"
              << std::left << std::setw(spacing) << "[5]    " << "Save / load System State *** NOT IMPELEMENTED ***\n"
              << std::left << std::setw(spacing) << "[6]    " << "Quit\n"
              << "*-----------*" << std::endl;
}

void Display::printHeader(const std::string& text) const {
    std::cout << "\n***************************************\n"
              << "********" << text << "********\n"
              << "***************************************\n" << std::endl;
}

void Display::printMessage(const std::string& text, bool lineBreak) const {
    std::cout << text;
    if (lineBreak) std::cout << " " << std::endl;
}

void Display::clear() {
    #ifdef _WIN32
    system("cls");
    return;
    #endif
    system("clear");
}