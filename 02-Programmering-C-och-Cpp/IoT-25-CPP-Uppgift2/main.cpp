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
        std::string name;
        float measuredVal;
    public:
        // Constructors
        MySensor() : deviceId(0), type("Unknown"), name("Unnamed"), measuredVal(0.0f) {}
        MySensor(int id) : deviceId(id) {}
        MySensor(int id, std::string t, std::string n, float temp) : deviceId(id), type(t), name(n), measuredVal(temp) {}
        
        void setType(std::string t) { type = t; }
        void setName(std::string n) { name = n; }
        void setVal(float newVal) { measuredVal = newVal; }
        
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

        // Constructors
        SystemManager() : numSensors(0) {}

        // Functions
        int getNumSensors() { return numSensors; }
        int nextSensorId() { return numSensors++; }
        void addSensor(MySensor& newSensor) { sensorsList.push_back(newSensor);}
        void takeReadings() {
            DataPoint newDataPoint;
            for (MySensor& s : sensorsList) {
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
    MySensor s1(manager.nextSensorId(), "temperature-sensor", "Temp sensor #1", 25.6);
    MySensor s2(manager.nextSensorId(), "humidity-sensor", "Humidity sensor", 43.1);

    manager.addSensor(s1);
    manager.addSensor(s2);

    manager.takeReadings();
    printData(manager.getReadings());

    std::cout << "Next reading: \n";
    int newVal = 0;
    for (MySensor& s : manager.sensorsList) {
        newVal += 10;
        s.setVal(newVal);
    }

    // MySensor s3(manager.nextSensorId(), "temperature-sensor", 17.1);
    // manager.addSensor(s3);

    manager.takeReadings();
    printData(manager.getReadings());
}

/*
ISSUES:
- System can't handle multiple of the same sensor.

BUGS:
*/