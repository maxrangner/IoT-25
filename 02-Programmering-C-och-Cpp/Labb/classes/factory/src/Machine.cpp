#include "Machine.h"

// PARENT
Machine::Machine(std::string type, std::vector<std::string> compatible)
    : machineType(type), isOn(false), compatibleComponents(compatible) {}

std::string Machine::getType() const { return machineType; };

void Machine::use() {
    std::cout << "I have no purpose..." << std::endl;
}

bool Machine::isAcceptedComponent(std::string input, const std::vector<std::string>& compatibleComponents) {
    for (const std::string& s : compatibleComponents) {
        if (input == s) return true;
    }
    return false;
}

void Machine::addComponent (MachineComponent* newComp) {
    if (isAcceptedComponent(newComp->getType(), compatibleComponents)) {
        installedParts.push_back(newComp);
    }
}

void Machine::viewComponents() {
    std::cout << "Components present: ";
    for (MachineComponent *mc : installedParts) {
        std::cout << mc->getType()
                  << "(" << mc->getWeight() << ")";
        if (mc != installedParts.back()) {
            std::cout << " | ";
        } else std::cout << std::endl;
    }
    std::cout << std::endl;
}

Machine::~Machine() {};

// CHILDREN
Assembler::Assembler() : Machine("Assembler") {}
void Assembler::use(MachineComponent& a, MachineComponent& b) {
    if (typeid(a) == typeid(MachineComponentMotor) && typeid(b) == typeid(MachineComponentBattery) || 
        typeid(a) == typeid(MachineComponentBattery) && typeid(b) == typeid(MachineComponentMotor)) {
            a.sound();
            b.sound();
            std::cout << "Assembled a device!" << std::endl;
    }
}