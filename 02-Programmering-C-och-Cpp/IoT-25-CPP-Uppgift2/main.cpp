#include <iostream>
#include <array>
#include <vector>
#include <fstream>


constexpr int NUM_DATAPOINTS = 5;

struct DataPoint {
    int deviceId;
    std::string type;
    float temperature;
};

class MySensor {
    private:
        int deviceId;
        std::string type;
        float temperature;
    public:
        MySensor() : deviceId(0), type("None"), temperature(0.0f) {}
        MySensor(int i) : deviceId(i) {}
        MySensor(int i, std::string t, float temp) : deviceId(i), type(t), temperature(temp) {}
        void setValue(float newVal) {
            temperature = newVal;
        }
        float readValue() {
            return temperature;
        }
        void printInfo() {
            std::cout << "DeviceID: " << deviceId << "\n"
                      << "Type: " << type << "\n"
                      << "Temperature: " << temperature << std::endl;
        }

};

class SystemManager {
    private:
        int numSensors;
        std::vector<MySensor> sensorList;
        std::vector<std::array<DataPoint, NUM_DATAPOINTS>> database;
    public:
        SystemManager() : numSensors(0) {}
        int getNumSensors() {
            return numSensors;
        }
        int nextSensorId() {
            numSensors++;
            return numSensors;
        }
        void addSensor(MySensor newSensor) {
            sensorList.push_back(newSensor);
        }
        void listSensors() {
            std::cout << "************************\n";
            for (MySensor s: sensorList) {
                s.printInfo();
                std::cout << "\n";
            }
            std::cout << "************************";
            std::cout << std::endl;
        }
        void collect() {
            for (std::array<DataPoint, NUM_DATAPOINTS> dp : database) {

            }
        }
};

bool writeToFile(std::vector<float> inpVec) {
    std::ofstream outFile("data.txt");
    if (!outFile) return false;
    for (float f : inpVec){
        outFile << f << std::endl;
    }
    outFile.close();
    return true;
}

bool readFromFile(float temp) {
    std::ofstream inFile("data.txt");
    if (!inFile) return false;
    inFile << temp << std::endl;
    inFile.close();
    return true;
}

int main() {
    // SystemManager manager;
    // MySensor s1(manager.nextSensorId(), "Temperature Sensor", 25.6);
    // MySensor s2(manager.nextSensorId(), "Humidity Sensor", 43.1);

    // manager.addSensor(s1);
    // manager.addSensor(s2);
    // manager.listSensors();

    std::vector<float> myVec;

    for (int i = 0; i < 5; i++) {
        std::string usrInp;
        std::cout << "> ";
        std::cin >> usrInp;
        myVec.push_back(stof(usrInp));
    }

    if (writeToFile(myVec)) std::cout << "Success!\n";
    else std::cout << "Error writing to file.\n";

    std::ifstream inFile("data.txt");

    std::string readLine;
    int sum = 0;
    while(std::getline(inFile, readLine)) {
        std::cout << readLine << std::endl;
        sum += std::stof(readLine);
    }

    std::cout << "Sum: " << sum;
}