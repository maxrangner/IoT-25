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
        void fileToSystemStateHistory(std::ifstream& file);
        void restoreSensors();
    public:
        SystemManager();
        std::map<time_t,std::vector<DataPoint>> systemStateHistory;
        int getNumSensors();
        int getNextSensorId();
        const std::vector<Sensor> getSensorsList();
        void addSensor(int type = 0);
        void removeSensor(int id);
        void collectReadings(int sensor = -1);
        void setSensorVal(int id, float val);
        std::vector<std::vector<DataPoint>> sortData();
        std::vector<DataPoint> findData(std::string searchStr);
        Statistics getStatistics();
        bool writeToFile();
        bool readFromFile();
        void resetSystem();
};

#endif