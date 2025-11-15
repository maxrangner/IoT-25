#include <iostream>
#include "Sensor.h"
#include "TemperatureSensor.h"
#include "definitions.h"
#include "utils.h"

// CONSTRUCTORS
TemperatureSensor::TemperatureSensor() {
    sensorId = getNextId();
    sensorType = SensorType::temperatureSensor;
    sensorUnit = "C";
    minMeasure = 0.0f;
    maxMeasure = 100.0f; 
    isActive_ = true;
}

TemperatureSensor::TemperatureSensor(int id) : Sensor(id) {
    sensorId = id;
    sensorType = SensorType::temperatureSensor;
    sensorUnit = "C";
    minMeasure = 0.0f;
    maxMeasure = 100.0f; 
    isActive_ = true;
}

Measurement TemperatureSensor::read() {
    Measurement newMeasurement;

    newMeasurement.sensorId = this->sensorId;
    newMeasurement.sensorType = this->sensorType;
    newMeasurement.sensorUnit = this->sensorUnit;
    newMeasurement.value = getRandomNumber(17.0f, 28.0f);
    newMeasurement.timestamp = getTime();

    return newMeasurement;
}