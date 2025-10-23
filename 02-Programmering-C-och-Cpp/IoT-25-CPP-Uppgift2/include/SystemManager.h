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
        int nextSensorId;
        int lastUpdateTime;
        std::vector<Sensor> sensorsList;
        std::time_t getTime();
        
    public:
        std::map<time_t,std::vector<DataPoint>> database;
        SystemManager();
        int getNumSensors();
        int getNextSensorId();
        void addSensor(int type = 0);
        void removeSensor(int id);
        void collectReadings(int sensor = -1);
        void setSensorVal(int id, float val);
        Statistics getStatistics();
        bool writeToFile();
        bool readFromFile();
        void resetSystem();
        const std::vector<Sensor>& getSensorsList();
        std::vector<std::vector<DataPoint>> sortData();
};

#endif