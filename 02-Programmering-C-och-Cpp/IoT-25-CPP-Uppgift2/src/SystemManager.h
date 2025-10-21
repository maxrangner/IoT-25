#ifndef MANAGER_HPP
#define MANAGER_HPP
#include <vector>
#include <ctime>
#include <map>
#include "definitions.h"
#include "Sensor.h"

class SystemManager {
    private:
        int numSensors;
        int lastUpdateTime;
        std::vector<MySensor> sensorsList;
        std::time_t getTime();
    public:
        std::map<time_t,std::vector<DataPoint>> database;
        SystemManager();
        int getNumSensors();
        int nextSensorId();
        void addSensor(int type);
        void makeSnapshot();
};

#endif