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

    myMachine.addComponent(a);
    myMachine.addComponent(b);
    myMachine.viewComponents();

    // myMachine.operate();
    // myAssembler.operate(a, b);

    return 0;
}
