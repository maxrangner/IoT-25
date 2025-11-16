#include <iomanip>
#include <array>
#include <vector>
#include <map>
#include <cmath>
#include "Display.h"
#include "utils.h"

void Display::printMenu() const {
    int spacing = 4;

    printHeader("MENU");
    std::cout << std::left << std::setw(spacing) << "[1]    " << "Add / remove sensor\n"
              << std::left << std::setw(spacing) << "[2]    " << "Status Screen\n"
              << std::left << std::setw(spacing) << "[3]    " << "Setup alarms\n"
              << std::left << std::setw(spacing) << "[4]    " << "Save / load System State\n"
              << std::left << std::setw(spacing) << "[5]    " << "Quit\n"
              << "*-----------*" << std::endl;
}

void Display::printHeader(const std::string& text) const {
    // clear();
    std::cout << "\033[30;47m\n*---" << text << "---*\n\033[0m"
              << std::endl;
}

void Display::printMessage(const std::string& text, bool lineBreak) const {
    std::cout << text;
    if (lineBreak) std::cout << " " << std::endl;
}

void Display::printMeasurement(const Measurement measurment) const {
    std::cout << "id: " << measurment.sensorId << " | "
            << "type: " << convertFromSensorType(measurment.sensorType) << " | "
            << measurment.value << " " << measurment.sensorUnit
            << std::endl;
}

void Display::printSensorsList(const std::vector<Measurement>& log, const std::vector<std::unique_ptr<Sensor>>& SensorsList, const Alarms& alarms) const {
    int numSensorsPrinted = 0;
    int spacing = 30;
    printMessage("****** Active sensors ******");

    for (auto& s : SensorsList) { // Loopa över varje sensor
        bool valueFound = false;
        
        for (auto it = log.rbegin(); it != log.rend(); ++it) {
            Measurement m = *it;
            if (s->getSensorId() == m.sensorId) {
                std::string color = formatStringColor(m, alarms);
                std::string coloredIdType = std::to_string(m.sensorId) + ": " + convertFromSensorType(m.sensorType) + ": ";
                std::string coloredValue = color + trimDecimals(m.value, 1) + "\033[0m";
                std::string coloredUnit = m.sensorUnit;

                std::cout << std::setw(26) << std::left << coloredIdType << std::setw(4) << std::left << coloredValue << coloredUnit;
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
}

void Display::printStats(std::vector<Measurement>& log) {
    Statistics newStats = getStatistics(log);
    
    if (newStats.numTemperaturePoints > 0) {
        std::cout << "\n*--- Temperature ---* Average: " << trimDecimals(newStats.averageTemperature, 2)
                                                        << " |   Min: " << newStats.minValTemperature
                                                        << " |   Max: " << newStats.maxValTemperature
                                                        << " |   Variance: " << trimDecimals(newStats.varianceTemperature, 2)
                                                        << " |   Std dev: " << trimDecimals(newStats.stdDeviationTemperature, 2);
    }
    if (newStats.numTemperaturePoints > 0) {
    std::cout << "\n*----- Humidity ----* Average: " << trimDecimals(newStats.averageHumidity, 2)
                                                    << " |   Min: " << newStats.minValHumidity
                                                    << " |   Max: " << newStats.maxValHumidity
                                                    << " |   Variance: " << trimDecimals(newStats.varianceHumidity, 2)
                                                    << " |   Std dev: " << trimDecimals(newStats.stdDeviationHumidity, 2) << std::endl;
    }
}

void Display::printAlarms(const Alarms& alarms) const {
    std::cout << ((alarms.isOn) ? "*--- Alarm is on ---* " : "*--- Alarm is off --* ")
            << "temperature: " << alarms.temperatureLow << " - " << alarms.temperatureHigh << "  |  "
            << "humidity: " << alarms.humidityLow << " - " << alarms.humidityHigh << std::endl
            << std::endl;
}

void Display::drawGraph(const std::array<Measurement, 10>& graphData, const Alarms& alarms) const {
    if (graphData.size() == 0) return;

    constexpr size_t TIME_RESOLUTION = 10;
    constexpr size_t MAX_GRAPH_RESOLUTION = 20;
    int graphResolution = MAX_GRAPH_RESOLUTION;
    int graphMinValue = 0;
    int rowMarkers = 0;
    std::array<int, 10> columnMarkers = {0};
    SensorType currentSensorType = graphData[9].sensorType;
    std::string sensorIdString = "";

    // Set graph for sensor type
    switch (currentSensorType) {
        case SensorType::temperatureSensor: graphMinValue = 15; graphResolution = 15; break;
        case SensorType::humiditySensor: graphMinValue = 45; graphResolution = 15; break;
        case SensorType::motionSensor: break;
        case SensorType::waterSensor: break;
        default: break;
    }

    rowMarkers = graphMinValue + graphResolution;

    // Initialize graph 2d array with empty spaces
    std::array<std::array<std::string, TIME_RESOLUTION>, MAX_GRAPH_RESOLUTION> graph;
    for (auto& col : graph) {
        std::fill(col.begin(), col.end(), "\033[90m---\033[0m");
    }

    // Place values in 2d array
    int column = TIME_RESOLUTION - 1;

    for (auto it = graphData.rbegin(); it != graphData.rend(); it++) {
        if (column < 0) break;
        const auto& measurement = *it;

        if (measurement.sensorId == -1) {
            column--;
            continue;
        } else {
            std::string typeColored = "\033[36m" + convertFromSensorType(measurement.sensorType) + "\033[0m"; 
            std::string idColored = "\033[36m" + std::to_string(measurement.sensorId) + "\033[0m"; 
            sensorIdString = measurement.sensorUnit + "   ***** " + typeColored + ": " + idColored + " *****";
        }
        
        int sensorValue = static_cast<int>(measurement.value - graphMinValue);

        // Limit values
        if (sensorValue < 0) sensorValue = 0;
        if (sensorValue >= graphResolution) sensorValue = graphResolution - 1;
    
        if (sensorValue > 0) {
            for (int row = 0; row < sensorValue - 1; row++) {
                graph[row][column] = "\033[43m   \033[0m";
            }
            std::string peakColor = formatStringColor(measurement, alarms);
            graph[sensorValue - 1][column] = peakColor + " x \033[0m";
        }
        column--;
    }
    
    // Draw graph
    printMessage(sensorIdString);
    for (int r = graphResolution - 1; r >= 0; r--) {
        std::cout << rowMarkers-- << " | "; // Draw values
        for (int c = 0; c < TIME_RESOLUTION; c++) {
            std::cout << graph[r][c];
            if (c != TIME_RESOLUTION - 1) std::cout << "\033[90m-----\033[0m";
        }
        std::cout << std::endl;
    }

    // Draw keys
    std::cout << "    ";
    for (int i = 0; i < graphData.size(); i++) {
        std::cout << formatTime(graphData[i].timestamp, false);
        if (i < graphData.size() - 1) std::cout << " | ";
    }
    std::cout << std::endl;
}

void Display::clear() const {
    #ifdef _WIN32
    system("cls");
    return;
    #endif
    system("clear");
}