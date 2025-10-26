#include "Machine.h"

// PARENT
Machine::Machine(std::string type) : machineType(type), isOn(false) {}
std::string Machine::getType() const { return machineType; };
void Machine::operate() {
    std::cout << "I have no purpose..." << std::endl;
}
void Machine::addComponent (MachineComponent* newComp) {
    if (isAcceptedComponent(newComp->getType(), acceptedComponents)) {
        installedParts.push_back(newComp);
    }
}
void Machine::viewComponents() {
    std::cout << "Components present: ";
    for (MachineComponent *mc : installedParts) {
        std::cout << mc->getType() << " | ";
    }
    std::cout << std::endl;
}
Machine::~Machine() {};

// CHILDREN
Assembler::Assembler() : Machine("Assembler") {}
void Assembler::operate(MachineComponent& a, MachineComponent& b) {
    if (typeid(a) == typeid(MachineComponentMotor) && typeid(b) == typeid(MachineComponentBattery) || 
        typeid(a) == typeid(MachineComponentBattery) && typeid(b) == typeid(MachineComponentMotor)) {
            a.sound();
            b.sound();
            std::cout << "Assembled a device!" << std::endl;
    }
}