#ifndef MACHINE_HPP
#define MACHINE_HPP
#include <iostream>
#include <vector>
#include "definitions.h"
#include "functions.h"
#include "MachineComponents.h"

// PARENT
class Machine {
    private:
        std::vector<std::string> acceptedComponents {"motor", "battery"};
    protected:
        std::string machineType;
        bool isOn;
        std::vector<MachineComponent*> installedParts;
    public:
        Machine(std::string type = "genericMachine");
        std::string getType() const;
        void operate();
        void addComponent (MachineComponent* newComp);
        void viewComponents();
        virtual ~Machine();
};

// CHILDREN
class Assembler : public Machine {
    public:
        Assembler();
        void operate(MachineComponent& a, MachineComponent& b);
};

#endif