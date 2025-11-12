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

void Display::drawGraph(const std::array<std::vector<Measurement>, 10>& graphData, int sensorId) const {
    /*
    15 rows (i) = values (15-30c)
    10 columns (j) = time
    TODO:
    - Input sensorId + Check valid sensorId
    */
    constexpr size_t graphResolution = 15;
    constexpr size_t timeEntires = 10;
    constexpr int graphMaxTemp = 30;

    // Initialize graph 2d array with empty spaces
    std::array<std::array<std::string, timeEntires>, graphResolution> graph;
    for (auto& col : graph) {
        std::fill(col.begin(), col.end(), " ");
    }

    // Place values
    int column = timeEntires - 1; // Start with right most column. -1 to align with indexing
    for (auto it = graphData.rbegin(); it != graphData.rend(); it++) { // Iterate backwards from the right
        if (column < 0) break;
        const auto& measurements = *it; // Create iterator reference to current measurement object, and dereference it.
        if (measurements.empty()) continue;

        float sensorValue = 0;
        for (auto& m : measurements) {
            if (m.sensorId == sensorId) {
                sensorValue = static_cast<int>(std::round(graphMaxTemp - m.value));
            }
        }
    
        for (int row = 0; row < sensorValue; row++) {
            graph[row][column] = "x";
        }
        graph[sensorValue][column--] = "\033[31mx\033[0m";
        // column--;
    }

    // Draw graph
    for (int row = graphResolution - 1; row >= 0; row--) {
        for (int column = 0; column < timeEntires; column++) {
            std::cout << graph[row][column] << "  ";
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