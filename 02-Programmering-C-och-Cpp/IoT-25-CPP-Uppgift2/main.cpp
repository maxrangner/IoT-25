#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <ctime>
#include <fstream>

constexpr int NUM_DATAPOINTS = 5;

enum sensorTypes{
    noType, // 0.
    temperatureSensor, // 1.
    humiditySensor, // 2.
    lightSensor, // 3.
    movementSensor, // 4.
};

struct DataPoint {
    int deviceId {};
    std::string type;
    float value {};
    bool isActive = true;
    bool isTriggered = false;
};

class MySensor {
    private:
        int deviceId {};
        int type;
        float value {};
        bool isActive = true;
        bool isTriggered = false;
    public:
        // Constructors
        MySensor() : deviceId(0), type(0), value(0.0f), isActive(true), isTriggered(false) {}
        MySensor(int id, int t) : deviceId(id), type(t) {}
        MySensor(int id,
                 int t,
                 float v,
                 bool a,
                 bool tr
                ) : deviceId(id), type(t), value(v), isActive(a), isTriggered(tr) {}
        
        // Retreivers
        int getId() { return deviceId; }
        int getType() { return type; }
        float getVal() { return value; }

        // Setters
        void setVal(float newVal) { value = newVal; }

        void printInfo() {
            std::cout << "************\n"
                      << "deviceId: " << deviceId << "\n"
                      << "type: " << type << "\n"
                      << "value: " << value << "\n"
                      << "isActive: " << isActive << "\n"
                      << "isTriggered: " << isTriggered << "\n";
        }
};

class SystemManager {
    private:
        int numSensors;
        int lastUpdateTime {};
        std::vector<MySensor> sensorsList;
        std::map<int,std::vector<DataPoint>> database;
    public:
        // Constructors
        SystemManager() : numSensors(0) {}

        // Functions
        int getNumSensors() { return numSensors; }
        int nextSensorId() { return numSensors++; }
        std::vector<MySensor> test() { return sensorsList; }
        void addSensor(int type) {
            sensorsList.emplace_back(nextSensorId(), type);
            numSensors = sensorsList.size();
        }
};

void printData(std::vector<DataPoint> data) {
    for (DataPoint dp : data) {
        std::cout << dp.type << ": " << dp.value;
        std::cout << std::endl;
    }
}

int main() {
    SystemManager manager;

    manager.addSensor(temperatureSensor);
    manager.addSensor(humiditySensor);

    for (MySensor s : manager.test()) {
        s.printInfo();
    }
}

/*
ISSUES:
- System can't handle multiple of the same sensor.

BUGS:
*/