#include "MachineComponents.h"

// PARENT
MachineComponent::MachineComponent(int w, std::string t) : weight(w), partType(t) {}
void MachineComponent::sound() {
    std::cout << "*Crickets*...\n";
}
int MachineComponent::getWeight() { return weight; }
std::string MachineComponent::getType() const { return partType; }

// CHILDREN
MachineComponentMotor::MachineComponentMotor(int w, std::string t) : MachineComponent(w, t) {}
void MachineComponentMotor::sound() {
    std::cout << "A says VRRRR!\n";
}

MachineComponentBattery::MachineComponentBattery(int w, std::string t) : MachineComponent(w, t) {}
void MachineComponentBattery::sound() {
    std::cout << "B says FZZZ!\n";
}

MachineComponentGripper::MachineComponentGripper(int w, std::string t) : MachineComponent(w, t) {}
void MachineComponentGripper::sound() {
    std::cout << "B says CLOMP!\n";
}

