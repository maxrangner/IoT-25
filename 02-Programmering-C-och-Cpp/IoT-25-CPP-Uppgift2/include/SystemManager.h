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
        std::vector<Sensor> sensorsList;
        std::time_t getTime();
        int nextSensorId();
        
    public:
        std::map<time_t,std::vector<DataPoint>> database;
        SystemManager();
        int getNumSensors();
        void addSensor(int type = 0);
        void removeSensor(int id);
        void collectReadings(int sensor = -1);
        bool writeToFile();
        bool readFromFile();
        void resetSystem();
        const std::vector<Sensor> getSensorsList();
};

#endif