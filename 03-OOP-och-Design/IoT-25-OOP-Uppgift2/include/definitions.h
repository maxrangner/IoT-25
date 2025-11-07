#pragma once
#include <string>

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
    // failInvalidInput,
    // failOutOfRange
};

enum class SensorType {
    temperatureSensor,
    humiditySensor,
    motionSensor,
    waterSensor
};

struct Measurement {
    int sensorId;
    SensorType sensorType;
    std::string sensorUnit;
    float value;
};

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