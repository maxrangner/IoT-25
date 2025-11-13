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

void Display::drawSensorsList(const std::vector<Measurement>& log, const std::vector<std::unique_ptr<Sensor>>& SensorsList) const {
    printMessage("****** Active sensors ******");
    for (auto& s : SensorsList) { // Loopa över varje sensor
        bool valueFound = false;
        
        for (auto it = log.rbegin(); it != log.rend(); ++it) {
            Measurement m = *it;
            if (s->getSensorId() == m.sensorId) {
                printMessage(std::to_string(m.sensorId), false);
                printMessage(":  ", false);
                printMessage(convertSensorType(m.sensorType), false);
                printMessage(": ", false);
                printMessage(trimDecimals(m.value, 1), false);
                printMessage(m.sensorUnit, false);
                printMessage(" | ", false);
                valueFound = true;
                break;
            }
        }
        if (!valueFound) {
            printMessage(std::to_string(s->getSensorId()), false);
            printMessage(" - ", false);
        }
    }
    printMessage(" ");
    printMessage("****************************");
}

void Display::drawGraph(const std::array<Measurement, 10>& graphData, int sensorId) const {
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
        const auto& measurement = *it; // Create iterator reference to current measurement object, and dereference it.
        if (measurement.sensorId != sensorId) {
            column--;
            continue;
        }

        float sensorValue = 0;
        sensorValue = static_cast<int>(std::round(graphMaxTemp - measurement.value));
        if (sensorValue < 0) sensorValue = 0;
        if (sensorValue >= graphResolution) sensorValue = graphResolution - 1;
    
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