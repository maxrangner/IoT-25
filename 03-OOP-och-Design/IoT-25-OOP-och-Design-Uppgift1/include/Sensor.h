#pragma once

class Sensor {
protected:
    float value;
public:
    Sensor();
    virtual void read() = 0;
};

class TemperatureSensor: public Sensor {
private:
    void read() override;
};

class HumiditySensor: public Sensor {
private:
    void read() override;
};