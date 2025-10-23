#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

constexpr int NUM_DATAPOINTS = 5;
constexpr int RANDOM_MIN = -100;
constexpr int RANDOM_MAX = 100;
constexpr int CHAR_ARRAY_SIZE = 50;
constexpr int DEFAULT_MIN_INPUT = -50;
constexpr int DEFAULT_MAX_INPUT = 50;

enum sensorTypes : int{
    noType, // 0.
    temperatureSensor, // 1.
    humiditySensor, // 2.
    lightSensor, // 3.
    movementSensor, // 4.
};

enum MenuSelection : int {
    startofMenu,
    addSensor, // 1.
    removeSensor, // 2.
    collectReadings, // 3.
    setSensorValue, // 4.
    dispData, // 5.
    sortData, // 6.
    findData, // 7.
    dispStats, // 8.
    save, // 9.
    load, // 10.
    quit, // 11.
    endOfMenu
};

enum validatorType : int {
    wholeNum = 1, // 1.
    decimalNum, // 2.
    text // 3.
};

struct DataPoint {
    int deviceId;
    int type;
    float value;
    bool isActive = true;
    bool isTriggered = false;
    DataPoint() : deviceId(0), type(0), value(0.0f), isActive(true), isTriggered(false) {}
    DataPoint(int id, int t, float v, bool a, bool tr)
        : deviceId(id), type(t), value(v), isActive(a), isTriggered(tr) {}
};

struct Statistics {
    bool empty = true;
    int numTimeStamps = 0;
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

#endif