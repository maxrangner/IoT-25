#pragma once
#include <string>

// CONSTS
constexpr int CHAR_ARRAY_SIZE = 50;

enum class MenuOptions {
    startOfMenu, // 0.
    addRemove, // 1.
    statusScreen, // 2.
    searchMeasure, // 3. 
    settings, // 4. 
    saveLoad, // 5.
    quit, // 6.
    endOfmenu // 7.
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

struct InputIntOrStringResult {
    FunctionReturnStatus status;
    std::string result;
};