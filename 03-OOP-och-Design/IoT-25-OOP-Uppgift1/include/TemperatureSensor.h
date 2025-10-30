#pragma once
#include "Sensor.h"
#include "Measurement.h"

class TemperatureSensor: public Sensor {
public:
    TemperatureSensor();
    Measurement read() override;
};