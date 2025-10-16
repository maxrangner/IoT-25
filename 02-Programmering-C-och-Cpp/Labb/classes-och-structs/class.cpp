#include <iostream>

class Sensor {
    private:
        int id;
        std::string name;
        float value;

    public:
        // CONSTURCTORS
        Sensor() : id(0), name("Unnamed"), value(0.0) {}
        Sensor(int i, std::string n) : id(i), name(n), value(0.0) {}
        Sensor(int i, std::string n, float v) : id(i), name(n), value(v) {}

        // FUNCTIONS
        void setValues(int i, std::string n, float v) {
            id = i;
            name = n;
            value = v;
        }
        void printInfo() {
            std::cout << "id: " << id << std::endl
                      << "name: " << name << std::endl
                      << "value: " << value << std::endl
                      << "------------------" << std::endl;
        }
        
};


int main() {
    Sensor s1;
    Sensor s2(2, "MySensor2");
    Sensor s3(3, "MySensor3", 25.3);

    s1.printInfo();
    s2.printInfo();
    s3.printInfo();

    return 0;
}