#include <iomanip>
#include <array>
#include <vector>
#include <map>
#include <cmath>
#include "Display.h"
#include "utils.h"

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

void Display::printMeasurement(const Measurement measurment) const {
    std::cout << "id: " << measurment.sensorId << " | "
            << "type: " << convertSensorType(measurment.sensorType) << " | "
            << measurment.value << " " << measurment.sensorUnit
            << std::endl;
}

void Display::drawGraph(const std::array<std::vector<Measurement>, 10>& graphData) const {
    /*
    15 rows (i) = values (15-30c)
    10 columns (j) = time
    */

    int minTemp = 15;
    int maxTemp = 30;
    int sensorId = 0;

    // Initialize graph
    std::array<std::array<std::string, 10>, 15> graph;
    for (int i = 0; i < 15; i++) { // ROWS
        for (int j = 0; j < 10; j++) { // COLUMNS
            graph[i][j] = " ";
        }
    }

    // Place values
    int column = 9;
    for (auto it = graphData.rbegin(); it != graphData.rend(); ++it) {
        if (column < 0) break;
        const auto& measurements = *it;
        if (measurements.empty()) continue;
        float value = measurements[sensorId].value;
        value = static_cast<int>(std::round(maxTemp - value));
        for (int row = 0; row < value; row++) {
            graph[row][column] = "x";
        }
        graph[value][column--] = "x";
    }

    for (int i = 14; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            std::cout << graph[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void Display::clear() {
    #ifdef _WIN32
    system("cls");
    return;
    #endif
    system("clear");
}