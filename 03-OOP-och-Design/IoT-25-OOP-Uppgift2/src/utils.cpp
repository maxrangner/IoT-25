#include <string>
#include <ctime>
#include <random>
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

float getRandomNumber(float min, float max) {
    std::random_device randDevice;
    std::mt19937 gen(randDevice());
    std::uniform_real_distribution<float> distrib(min, max);
    float returnVal = distrib(gen);

    return std::round(returnVal * 100.0f) / 100.0f;
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