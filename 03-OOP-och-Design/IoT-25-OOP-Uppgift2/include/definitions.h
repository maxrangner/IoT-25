#pragma once
#include <string>

// CONSTS
constexpr int CHAR_ARRAY_SIZE = 50;
constexpr int THREAD_SLEEP_MS = 100;

enum class MenuOptions {
    startOfMenu, // 0.
    addRemove, // 1.
    statusScreen, // 2. 
    settings, // 3. 
    saveLoad, // 4.
    quit, // 5.
    endOfmenu // 6.
};

enum class FunctionReturnStatus {
    success,
    fail,
    none
};

enum class SensorType {
    unknownSensor,
    temperatureSensor,
    humiditySensor,
    motionSensor,
    waterSensor
};

// Return type for the Sensors.
struct Measurement {
    int sensorId = -1;
    SensorType sensorType = SensorType::unknownSensor;
    std::string sensorUnit = "";
    float value = 0.0f;
    time_t timestamp = 0;
};

// INPUT RESULTS - These returns a status struct along with the return value.
struct InputIntResult {
    FunctionReturnStatus status;
    int result;
};

struct InputStringResult {
    FunctionReturnStatus status;
    std::string result;
};

struct Alarms {
    bool isOn = true;

    float temperatureLow = 18.0f;
    float temperatureHigh = 26.0f;
    float humidityLow = 48.0f;
    float humidityHigh = 56.0f;
};

struct Statistics {
    bool empty = true;

    // Temperature
    int numTemperaturePoints = 0;
    double sumTemperature = 0.0;
    double averageTemperature = 0.0;
    double varianceTemperature = 0.0;
    float stdDeviationTemperature = 0.0f;
    float minValTemperature = 0.0f;
    float maxValTemperature = 0.0f;
    //Humidity
    int numHumidityPoints = 0;
    double sumHumidity = 0.0;
    double averageHumidity = 0.0;
    double varianceHumidity = 0.0;
    float stdDeviationHumidity = 0.0f;
    float minValHumidity = 0.0f;
    float maxValHumidity = 0.0f;
};