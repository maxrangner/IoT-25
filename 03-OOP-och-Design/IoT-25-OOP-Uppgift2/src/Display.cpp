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
              << std::left << std::setw(spacing) << "[3]    " << "Settings *** NOT IMPELEMENTED ***\n"
              << std::left << std::setw(spacing) << "[4]    " << "Save / load System State *** NOT IMPELEMENTED ***\n"
              << std::left << std::setw(spacing) << "[5]    " << "Quit\n"
              << "*-----------*" << std::endl;
}

void Display::printHeader(const std::string& text) const {
    clear();
    std::cout << "\n*---" << text << "---*\n"
              << std::endl;
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

void Display::printSensorsList(const std::vector<Measurement>& log, const std::vector<std::unique_ptr<Sensor>>& SensorsList) const {
    int numSensorsPrinted = 0;
    int spacing = 30;
    printMessage("****** Active sensors ******");
    for (auto& s : SensorsList) { // Loopa över varje sensor
        bool valueFound = false;
        
        for (auto it = log.rbegin(); it != log.rend(); ++it) {
            Measurement m = *it;
            if (s->getSensorId() == m.sensorId) {
                std::string sensorStringFirst;
                std::string sensorStringSecond;
                sensorStringFirst += std::to_string(m.sensorId);
                sensorStringFirst += ": ";
                sensorStringFirst += convertSensorType(m.sensorType);
                sensorStringFirst += ": ";
                sensorStringSecond += trimDecimals(m.value, 1);
                sensorStringSecond += m.sensorUnit;

                std::cout << std::setw(26) << std::left << sensorStringFirst << std::setw(8) << std::left << sensorStringSecond;
                numSensorsPrinted++;

                if (numSensorsPrinted < 3) {
                    std::cout << " | ";
                    
                } else {
                    std::cout << std::endl;
                    numSensorsPrinted = 0;
                }
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

void Display::drawGraph(const std::array<Measurement, 10>& graphData) const {
    constexpr size_t timeEntires = 10;
    constexpr size_t MAX_GRAPH_RESOLUTION = 20;
    int graphResolution = 15;
    int valueMarker;
    int graphMinTemp;
    SensorType currentSensorType = graphData[9].sensorType;

    switch (currentSensorType) {
        case SensorType::temperatureSensor: {
            graphMinTemp = 15;
            break;
        }
        case SensorType::humiditySensor: {
            graphMinTemp = 45;
            break;
        }
        case SensorType::motionSensor: break;
        case SensorType::waterSensor: break;
        default: {
            graphResolution = MAX_GRAPH_RESOLUTION;
            graphMinTemp = 0;
            break;
        }; 
    }
    valueMarker = graphMinTemp + graphResolution;

    // Initialize graph 2d array with empty spaces
    std::array<std::array<std::string, timeEntires>, MAX_GRAPH_RESOLUTION> graph;
    for (auto& col : graph) {
        std::fill(col.begin(), col.end(), "\033[390m-\033[0m");
    }

    // Place values
    int column = timeEntires - 1;
    for (auto it = graphData.rbegin(); it != graphData.rend(); it++) {
        if (column < 0) break;
        const auto& measurement = *it;

        if (measurement.sensorId == -1) {
            column--;
            continue;
        }
        int sensorValue = static_cast<int>(measurement.value - graphMinTemp);

        // Limit values
        if (sensorValue < 0) sensorValue = 0;
        if (sensorValue >= graphResolution) sensorValue = graphResolution - 1;
    
        if (sensorValue > 0) {
            for (int row = 0; row < sensorValue - 1; row++) {
                graph[row][column] = "\033[33mx\033[0m";
            }
            graph[sensorValue - 1][column] = "\033[32mx\033[0m";
        }
        column--;
    }

    // Draw graph
    for (int r = graphResolution - 1; r >= 0; r--) {
        std::cout << valueMarker-- << "|";
        for (int c = 0; c < timeEntires; c++) {
            std::cout << graph[r][c] << "  ";
        }
        std::cout << std::endl;
    }
}

void Display::clear() const {
    #ifdef _WIN32
    system("cls");
    return;
    #endif
    system("clear");
}