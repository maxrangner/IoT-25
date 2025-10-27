#ifndef MACHINE_HPP
#define MACHINE_HPP
#include <iostream>
#include <vector>
#include "definitions.h"
#include "functions.h"
#include "MachineComponents.h"

// PARENT
class Machine {
     protected:
        std::string machineType;
        std::vector<std::string> compatibleComponents {"motor", "battery"};
        std::vector<MachineComponent*> installedParts;
        bool isOn;
        
    public:
        Machine(std::string type = "genericMachine", std::vector<std::string> compatible = {"motor", "battery"});
        std::string getType() const;
        void use();
        bool isAcceptedComponent(std::string input, const std::vector<std::string>& compatibleComponents);
        void addComponent (MachineComponent* newComp);
        void removeComponent(MachineComponent* compToRemove);
        void viewComponents();
        virtual ~Machine();
};

// CHILDREN
class Assembler : public Machine {
    public:
        Assembler();
        void use(MachineComponent& a, MachineComponent& b);
};

#endif