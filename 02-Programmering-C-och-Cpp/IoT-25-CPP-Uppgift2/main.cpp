#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <ctime>
#include <fstream>

struct DataPoint {
    float temperature {};
    float humidity {};
    int timestamp {};
};

constexpr int NUM_DATAPOINTS = 5;

class MySensor {
    private:
        int deviceId;
        std::string type;
        float measuredVal;
    public:
        // Constructors
        MySensor() : deviceId(0), type("Unknown"), measuredVal(0.0f) {}
        MySensor(int id) : deviceId(id) {}
        MySensor(int id, std::string t, float temp) : deviceId(id), type(t), measuredVal(temp) {}
        
        void setVal(float newVal) {measuredVal = newVal; }
        int getId() { return deviceId; }
        std::string getType() { return type; }
        float getVal() { return measuredVal; }
};

class SystemManager {
    private:
        int numSensors;
        
        std::vector<DataPoint> database;
    public:
        std::vector<MySensor> sensorsList;

        SystemManager() : numSensors(0) {}
        int getNumSensors() { return numSensors; }
        int nextSensorId() { return numSensors++; }
        void addSensor(MySensor newSensor) { sensorsList.push_back(newSensor);}
        void takeReadings() {
            DataPoint newDataPoint;
            for (MySensor s : sensorsList) {
                if (s.getType() == "temperature-sensor") newDataPoint.temperature = s.getVal();
                if (s.getType() == "humidity-sensor") newDataPoint.humidity = s.getVal();
                newDataPoint.timestamp = 2025;
                // newDataPoint.timestamp = getTime();
            }
            database.push_back(newDataPoint);
        }
        std::vector<DataPoint> getReadings() { return database; }
};

void printData(std::vector<DataPoint> data) {
    for (DataPoint dp : data) {
        std::cout << dp.timestamp << " - "
                  << "Temperature: " << dp.temperature << " "
                  << "Humidity: " << dp.humidity << " ";
        std::cout << std::endl;
    }
}

int main() {
    SystemManager manager;
    MySensor s1(manager.nextSensorId(), "temperature-sensor", 25.6);
    MySensor s2(manager.nextSensorId(), "humidity-sensor", 43.1);

    manager.addSensor(s1);
    manager.addSensor(s2);

    for (MySensor s : manager.sensorsList) {
        s.setVal(10);
    }
    manager.takeReadings();
    printData(manager.getReadings());

    std::cout << "Next reading: \n";

    MySensor s2(manager.nextSensorId(), "humidity-sensor", 43.1);

    for (MySensor s : manager.sensorsList) {
        s.setVal(20);
    }
    manager.takeReadings();

    printData(manager.getReadings());
}

/*
ISSUES:
- System can't handle multiple of the same sensor.

BUGS:
- s.setVal() does not update value.
*/