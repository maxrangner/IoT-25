#pragma once
#include "Sensor.h"
#include "definitions.h"

class TemperatureSensor: public Sensor {
public:
    TemperatureSensor();
    TemperatureSensor(int id);
    Measurement read() override;
};