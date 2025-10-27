#include <iostream>
#include <vector>
#include "definitions.h"
#include "functions.h"
#include "MachineComponents.h"
#include "Machine.h"



int main() {
    Machine myMachine;
    Assembler myAssembler;
    MachineComponentMotor* a = new MachineComponentMotor(10);
    MachineComponentBattery* b = new MachineComponentBattery(2);
    MachineComponentBattery* c = new MachineComponentBattery(5);


    myAssembler.addComponent(a);
    myAssembler.addComponent(b);
    myAssembler.viewComponents();
    myAssembler.addComponent(c);
    myAssembler.viewComponents();

    // myMachine.use();
    // myAssembler.use(a, b);

    return 0;
}
