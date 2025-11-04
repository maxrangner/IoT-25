#include <iomanip>
#include "Display.h"

void Display::printMenu() const {
    int spacing = 4;

    std::cout << "\n*--- MENU ---*\n"
              << std::left << std::setw(spacing) << "1." << "Setup: Add / remove sensor\n"
              << std::left << std::setw(spacing) << "2." << "Setup: Update interval\n"
              << std::left << std::setw(spacing) << "3." << "Display: Historical Graph\n"
              << std::left << std::setw(spacing) << "4." << "Display: Statistics\n"
              << std::left << std::setw(spacing) << "5." << "Search: By time\n"
              << std::left << std::setw(spacing) << "6." << "Search: By value\n"
              << std::left << std::setw(spacing) << "7." << "Save / load System State\n"
              << std::left << std::setw(spacing) << "8." << "Quit\n"
              << "*-----------*" << std::endl;
}

void Display::printHeader(const std::string& text) const {
    std::cout << "\n***************************************\n"
              << "********" << text << "********\n"
              << "***************************************\n" << std::endl;
}

void Display::printMessage(const std::string& text) const {
    std::cout << text << std::endl;
}

void clear() {
    std::cout << "\033c";
}