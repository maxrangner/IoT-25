#include "definitions.h"
#include <map>
#include <vector>
#include <string>

std::map<std::string, std::vector<std::string>> recepies = {
   {"genericMachine", {}},
   {"MachineAssembler", {"motor", "battery"}}, 
   {"MachineWelder", {"motor", "battery"}},
   {"MachineCutter", {"motor", "battery", "cutter"}}
};