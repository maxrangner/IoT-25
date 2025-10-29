#ifndef MACHINECOMPONENTS_HPP
#define MACHINECOMPONENTS_HPP
#include <iostream>
#include <vector>
#include "definitions.h"
#include "functions.h"

// PARENT
class MachineComponent {
private:
    std::string partType;
    int weight;
    
public:
    MachineComponent(int w = 0, std::string t = "genericPart");
    virtual void sound();
    int getWeight();
    std::string getType() const;
};

// CHILDREN
class MachineComponentMotor : public MachineComponent {
public:
    MachineComponentMotor(int w = 0, std::string t = "motor");
    void sound() override;
};

class MachineComponentBattery : public MachineComponent {
public:
    MachineComponentBattery(int w = 0, std::string t = "battery");
    void sound() override;
};

class MachineComponentGripper : public MachineComponent {
public:
    MachineComponentGripper(int w = 0, std::string t = "gripper");
    void sound() override;
};

#endif