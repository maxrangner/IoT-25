#include <iostream>
#include "Sensor.h"
#include "TemperatureSensor.h"
#include "definitions.h"
#include "utils.h"

TemperatureSensor::TemperatureSensor() {
    sensorId = getNextId();
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
    newMeasurement.value = getRandomNumber();

    return newMeasurement;
}