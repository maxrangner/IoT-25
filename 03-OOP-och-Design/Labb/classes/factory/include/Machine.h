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
    std::vector<MachineComponent*> installedParts;
    bool isOn;
    
public:
    // CONSTRUCTORS
    Machine(std::string type = "genericMachine");
    //GETTERS
    std::string getType() const;
    // TOOLS
    bool isAcceptedComponent(std::string input, const std::vector<std::string>& compatibleComponents);
    bool hasCorrectComponents();
    // CORE
    virtual void use() = 0;
    void addComponent(MachineComponent* newComp);
    void removeComponent(MachineComponent* compToRemove);
    void viewComponents();
    // DESTRUCTORS
    virtual ~Machine();
};

// CHILDREN
class Assembler : public Machine {
private:

public:
    // CONSTRUCTORS
    Assembler();
    // CORE
    void use() override;
};

#endif