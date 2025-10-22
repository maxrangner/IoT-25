#ifndef SENSOR_HPP
#define SENSOR_HPP
#include "definitions.h"

class Sensor {
    private:
        int deviceId;
        int type;
        float value;
        bool isActive;
        bool isTriggered;
    public:
        // Constructors
        Sensor();
        Sensor(int id, int t);
        Sensor(int id, int t, float v, bool a, bool tr);
        int getId();
        int getType();
        DataPoint getStatus() const;
        void setValue(float val);
        void updateReading();
        void printInfo();
};

#endif