#ifndef MANAGER_HPP
#define MANAGER_HPP
#include <vector>
#include <ctime>
#include <map>
#include "definitions.h"
#include "functions.h"
#include "Sensor.h"

class SystemManager {
    private:
        int numSensors;
        int lastUpdateTime;
        std::vector<MySensor> sensorsList;
        std::time_t getTime();
        int nextSensorId();
        int getNumSensors();
    public:
        std::map<time_t,std::vector<DataPoint>> database;
        SystemManager();
        void addSensor(int type);
        // void removeSensor(int id);
        void makeSnapshot();
        void resetSystem();
};

#endif