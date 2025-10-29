#include <iostream>
#include <vector>
#include "definitions.h"
#include "functions.h"
#include "MachineComponents.h"
#include "Machine.h"

int main() {
    Machine* myAssembler = new Assembler;
    MachineComponentMotor* a = new MachineComponentMotor(10);
    MachineComponentBattery* b = new MachineComponentBattery(2);
    MachineComponentGripper* c = new MachineComponentGripper(5);
    myAssembler->use();

    myAssembler->addComponent(a);
    myAssembler->viewComponents();
    myAssembler->use();

    myAssembler->addComponent(c);
    myAssembler->addComponent(b);
    myAssembler->viewComponents();
    myAssembler->use();
    
    return 0;
}
