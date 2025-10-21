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
    int type;
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
        MySensor(int id, int t, float v, bool a, bool tr)
                 : deviceId(id), type(t), value(v), isActive(a), isTriggered(tr) {}
        
        // Retreive data
        int getId() { return deviceId; }
        int getType() { return type; }
        DataPoint getStatus() {
            DataPoint newDP;
            newDP.deviceId = deviceId;
            newDP.type = type;
            newDP.value = value;
            newDP.isActive = isActive;
            newDP.isTriggered = isTriggered;
            return newDP;
        }

        // Set data
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
        // std::map<time_t,std::vector<DataPoint>> database;
        std::time_t getTime() {
            std::time_t timestamp = std::time(nullptr);
            return timestamp;
        }
    public:
        std::map<time_t,std::vector<DataPoint>> database;
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
        void makeSnapshot() {
            time_t newTimestamp = getTime();
            database[newTimestamp];
            std::vector<DataPoint> data;
            for (MySensor s : sensorsList) {
                data.push_back(s.getStatus());
            }
            database[newTimestamp] = data;
        }
};

int main() {
    SystemManager manager;

    manager.addSensor(temperatureSensor);
    manager.addSensor(humiditySensor);

    // for (MySensor s : manager.test()) {
    //     s.printInfo();
    // }
    manager.makeSnapshot();
    std::cin.get();
    manager.makeSnapshot();

    for (auto& pair : manager.database) {
        std::cout << "Timestamp: " << pair.first << ":\n";
        for (auto& v : pair.second) {
            std::cout << "**************\n"
                      << "deviceId: " << v.deviceId << "\n"
                      << "type: " << v.type << "\n"
                      << "value: " << v.value << "\n"
                      << "isActive: " << v.isActive << "\n"
                      << "isTriggered: " << v.isTriggered << "\n";
        }
        std::cout << std::endl;
    }
}

/*
ISSUES:
- System can't handle multiple of the same sensor.

BUGS:
*/