#ifndef SENSOR_HPP
#define SENSOR_HPP
#include "definitions.h"

class MySensor {
    private:
        int deviceId;
        int type;
        float value;
        bool isActive;
        bool isTriggered;
    public:
        // Constructors
        MySensor();
        MySensor(int id, int t);
        MySensor(int id, int t, float v, bool a, bool tr);
        int getId();
        int getType();
        DataPoint getStatus();
        void setVal(float newVal);
        void printInfo();
};

#endif