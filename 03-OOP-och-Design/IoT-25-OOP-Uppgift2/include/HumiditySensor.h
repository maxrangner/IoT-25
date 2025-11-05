#pragma once
#include "Sensor.h"
#include "definitions.h"

class HumiditySensor: public Sensor {
public:
    HumiditySensor();
    Measurement read() override;
};