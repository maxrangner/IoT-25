#include <algorithm>
#include "Machine.h"

// PARENT
Machine::Machine(std::string type)
    : machineType(type), isOn(false) {}

//GETTERS
std::string Machine::getType() const { return machineType; };

// TOOLS
bool Machine::isAcceptedComponent(std::string input, const std::vector<std::string>& compatibleComponents) {
    for (const std::string& s : compatibleComponents) {
        if (input == s) return true;
    }
    return false;
}

bool Machine::hasCorrectComponents() {
    return std::all_of(recepies[getType()].begin(), recepies[getType()].end(),
        [this] (const std::string& s) {
            return std::any_of(
                installedParts.begin(), installedParts.end(),
                [this, &s](MachineComponent* c) {
                    return c->getType() == s;
                }
            );
        }
    );
}

// CORE
void Machine::use() {}


void Machine::addComponent (MachineComponent* newComponent) {
    if (isAcceptedComponent(newComponent->getType(), recepies[this->getType()])) {
        std::string name = newComponent->getType();
        name[0] = std::toupper(name[0]);
        std::cout << name << " installed!\n";
        installedParts.push_back(newComponent);
    } else {
        std::cout << "Not accepted component.\n";
    }
}

void Machine::removeComponent(MachineComponent* compToRemove) {
    for (auto i = 0; i < installedParts.size(); i++) {
        if (compToRemove == installedParts[i]) {
            installedParts.erase(installedParts.begin() + i);
            return;
        }
    }
}

void Machine::viewComponents() {
    std::cout << "\n***** Components present *****\n";
    for (MachineComponent *mc : installedParts) {
        std::cout << mc->getType()
                  << "(" << mc->getWeight() << ")";
        if (mc != installedParts.back()) {
            std::cout << " | ";
        } else std::cout << std::endl;
    }
    std::cout << "******************************\n"
              << std::endl;
}

// DESTRUCTORS
Machine::~Machine() {};

// CHILDREN
Assembler::Assembler() : Machine("MachineAssembler") {}
void Assembler::use() {
    if (!hasCorrectComponents()) {
        std::cout << "Not enough components.\n"; 
        return;
    }
    std::cout << "Working!\n";
}