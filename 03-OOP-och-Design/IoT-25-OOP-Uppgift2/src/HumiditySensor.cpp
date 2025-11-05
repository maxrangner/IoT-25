#include <iostream>
#include "Sensor.h"
#include "HumiditySensor.h"
#include "definitions.h"

HumiditySensor::HumiditySensor() {
    sensorId = getNextId();
    sensorType = SensorType::humiditySensor;
    sensorUnit = "%";
    minMeasure = 0.0f;
    maxMeasure = 100.0f; 
    isActive_ = true;
}
Measurement HumiditySensor::read() {
    Measurement newMeasurement;
    newMeasurement.sensorId = sensorId;
    newMeasurement.sensorType = sensorType;
    newMeasurement.sensorUnit = sensorUnit;

    return newMeasurement;
}