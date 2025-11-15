#include <string>
#include <ctime>
#include <random>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "utils.h"
// #include "definitions.h"

std::string makeLower(std::string input) {
    std::string output = "";
    for (const char& c : input) {
        output += std::tolower(c);
    }
    return output;
}

std::string convertFromSensorType(SensorType type) {
    switch (type) {
        case SensorType::temperatureSensor: return "temperature sensor";
        case SensorType::humiditySensor: return "humidity sensor";
        case SensorType::motionSensor: return "motion sensor";
        case SensorType::waterSensor: return "water sensor";
        default: return "unknown";
    }
}

SensorType convertToSensorType(std::string type) {
    if (type == "temperature sensor") return SensorType::temperatureSensor;
    if (type == "humidity sensor") return SensorType::humiditySensor;
    if (type == "motion sensor") return SensorType::motionSensor;
    if (type == "water sensor") return SensorType::waterSensor;
    else return SensorType::unknownSensor;
}

float getRandomNumber(float min, float max) {
    static std::random_device randDevice;
    static std::mt19937 gen(randDevice());
    std::uniform_real_distribution<float> distrib(min, max);
    float returnVal = distrib(gen);

    return std::round(returnVal * 100.0f) / 100.0f; // Rounds return to two decimals
}

time_t getTime() { // Returns current time
    time_t timestamp;
    std::time(&timestamp);
    return timestamp;
}

std::string readTime(std::time_t timestamp) { // Converts time_t to a readable string
    struct tm currentTime = *localtime(&timestamp);
    char time[CHAR_ARRAY_SIZE];
    strftime(time, sizeof(time), "%a%e %b %H:%M:%S", &currentTime);
    return time;
}

std::string sensorTypeToString(SensorType type) {
    switch (type) {
        case SensorType::temperatureSensor: return "Temperature Sensor";
        case SensorType::humiditySensor: return "Humidity Sensor";
        case SensorType::motionSensor: return "Motion Sensor";
        case SensorType::waterSensor: return "Water Sensor";
        default: return "unknown";
    }
}

std::string trimDecimals(float value, int precision) {
    std::string returnString;
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;
    returnString = ss.str();
    return returnString;
}

Statistics getStatistics(std::vector<Measurement>& log) {
    Statistics outputStats; 
    if (log.empty()) return outputStats;

    bool firstTemperatureRun = true;
    bool firstHumidityRun = true;

    for (const auto& Measurment : log) {
        switch (Measurment.sensorType) {
            case SensorType::temperatureSensor: {
                if (firstTemperatureRun) {
                    outputStats.minValTemperature = Measurment.value;
                    outputStats.maxValTemperature = Measurment.value;
                    firstTemperatureRun = false;
                }

                outputStats.sumTemperature += Measurment.value;

                if (Measurment.value < outputStats.minValTemperature) {
                    outputStats.minValTemperature = Measurment.value;
                }
                if (Measurment.value > outputStats.maxValTemperature) {
                    outputStats.maxValTemperature = Measurment.value;
                }
                outputStats.numTemperaturePoints++;
                break;
            }
            case SensorType::humiditySensor: {
                if (firstHumidityRun) {
                    outputStats.minValHumidity = Measurment.value;
                    outputStats.maxValHumidity = Measurment.value;
                    firstHumidityRun = false;
                } 

                outputStats.sumHumidity += Measurment.value;

                if (Measurment.value < outputStats.minValHumidity) {
                    outputStats.minValHumidity = Measurment.value;
                }
                if (Measurment.value > outputStats.maxValHumidity) {
                    outputStats.maxValHumidity = Measurment.value;
                }
                outputStats.numHumidityPoints++;
                break;
            }
            case SensorType::motionSensor: break;
            case SensorType::waterSensor: break;
            default: break;
        }
    }

    if (outputStats.numTemperaturePoints) outputStats.averageTemperature = outputStats.sumTemperature / outputStats.numTemperaturePoints;
    if (outputStats.numHumidityPoints) outputStats.averageHumidity = outputStats.sumHumidity / outputStats.numHumidityPoints;

    for (const auto& Measurement : log) {
        switch (Measurement.sensorType) {
            case SensorType::temperatureSensor: {
                outputStats.varianceTemperature += (Measurement.value - outputStats.averageTemperature) * (Measurement.value - outputStats.averageTemperature);
                break;
            }
            case SensorType::humiditySensor: {
                outputStats.varianceHumidity += (Measurement.value - outputStats.averageHumidity) * (Measurement.value - outputStats.averageHumidity);
                break;
            }
            default:
                break;
        }
    }

    if (outputStats.numTemperaturePoints > 0) {
        outputStats.varianceTemperature = outputStats.varianceTemperature / outputStats.numTemperaturePoints;
        outputStats.stdDeviationTemperature = std::sqrt(outputStats.varianceTemperature);
    }
    if (outputStats.numHumidityPoints > 0) {
        outputStats.varianceHumidity = outputStats.varianceHumidity / outputStats.numHumidityPoints;
        outputStats.stdDeviationHumidity = std::sqrt(outputStats.varianceHumidity);   
    }
    
    outputStats.empty = false;
    return outputStats;
}