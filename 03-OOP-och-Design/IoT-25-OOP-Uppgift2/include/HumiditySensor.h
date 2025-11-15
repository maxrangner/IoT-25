#pragma once
#include "Sensor.h"
#include "definitions.h"

class HumiditySensor: public Sensor {
public:
    HumiditySensor();
    HumiditySensor(int id);
    Measurement read() override;
};