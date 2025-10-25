#include <iostream>
#include "definitions.h"

class Material {
    private:
        int resourceType;
    public:
        Material(int type = 0) : resourceType(type) {}
        int getObjectType() {
            return resourceType;
        }
};

class machine {
    private:
        
    protected:
        std::string typeName;
        bool isOn;
    public:
        machine(std::string type = "genericMachine")
            : typeName(type), isOn(false) {}
        void toggleOnOff() {
            isOn = !isOn;
        }
        void getStatus() {
            std::cout << "isOn: " << (isOn ? "on" : "off")
                      << " | type: " << typeName
                      << std::endl;
        }
        void operate() {
            std::cout << "I have no purpose..." << std::endl;
        }
};

class assembler : public machine {
    private:

    public:
        assembler() : machine("assembler") {}
        void operate(Material a, Material b) {
            if (a.getObjectType() == Materials::wood && b.getObjectType() == Materials::metal || 
                a.getObjectType() == Materials::metal && b.getObjectType() == Materials::wood) {
                std::cout << "Assembled an axe!" << std::endl;
            }
            if (a.getObjectType() == Materials::metal && b.getObjectType() == Materials::metal) {
                std::cout << "Assembled a metal plate!" << std::endl;
            }
            if (a.getObjectType() == Materials::wood && b.getObjectType() == Materials::wood) {
                std::cout << "Assembled a wooden stick!" << std::endl;
            }
        }
};

int main() {
    machine myMachine;
    assembler myAssembler;
    Material a(wood);
    Material b(metal);

    // myMachine.operate();
    myAssembler.operate(a, a);
    myAssembler.operate(b, b);
    myAssembler.operate(a, b);

    return 0;
}