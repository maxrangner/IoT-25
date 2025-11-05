#include <string>
#include "utils.h"
// #include "definitions.h"

std::string makeLower(std::string input) {
    std::string output = "";
    for (const char& c : input) {
        output += std::tolower(c);
    }
    return output;
}

std::string convertSensorType(SensorType type) {
    switch (type) {
        case SensorType::temperatureSensor: return "temperature sensor";
        case SensorType::humiditySensor: return "humidity sensor";
        case SensorType::motionSensor: return "motion sensor";
        case SensorType::waterSensor: return "water sensor";
        default: return "unknown";
    }
}