#include <iostream>

struct Device {
    int id;
    std::string type;
    bool active;
    float value;

    void printDevice() {
        std::cout << "Device ID: " << id << std::endl
                << "Type: " << type << std::endl
                << (active ? "Is active" : "Is not active") << std::endl
                << "Value: " << value << std::endl;
    } 

};

// void printDevice(const Device& d) {
//     std::cout << "Device ID: " << d.id << std::endl
//               << "Type: " << d.type << std::endl
//               << (d.active ? "Is active" : "Is not active") << std::endl
//               << "Value: " << d.value << std::endl;
// }

int main() {
    Device d1 = {1, "temp sensor", true, 25.5f}; // stacken
    Device* d2 = new Device{2, "temp sensor", false, 23.5f}; // heapen

    // if (d1.active) {
    //     std::cout << "d1 is active\n";
    // }
    // if (d2.active) {
    //     std::cout << "d2 is active";
    // }

    // d1.printDevice();
    // d1.active = false;
    // d1.printDevice();

    d1.value = 1.1;
    d2->value = 2.2;

    std::cout << d1.id << " -> minnesplats: " << &d1 << " -> value: " << d1.value << std::endl
              << d2->id << " -> minnesplats: " << d2 << " -> value: " << d2->value << std::endl
            //   << (*d2).id
              << std::endl;

    delete d2;
    
    return 0;
}