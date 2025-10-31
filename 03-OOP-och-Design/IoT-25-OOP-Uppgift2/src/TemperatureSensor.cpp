#include <iostream>
#include "Sensor.h"
#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor() {
    sensorId = getNextId();
    sensorType = "Temperature Sensor";
    sensorUnit = "C";
    minMeasure = 0.0f;
    maxMeasure = 100.0f; 
    isActive = true;
}
Measurement TemperatureSensor::read() {
    Measurement newMeasurement;
    newMeasurement.sensorId = sensorId;
    newMeasurement.sensorType = sensorType;
    newMeasurement.sensorUnit = sensorUnit;

    return newMeasurement;
}