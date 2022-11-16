#include "Bus.h"
#include <iostream>

int main(){
    Bus bus;

    std::cout << std::hex << (int)bus.cpu.read(0x00FF) << std::endl;
    bus.cpu.write(0x00FF,0xA1);
    std::cout << std::hex << (int)bus.cpu.read(0x00FF) << std::endl;
    std::cout << "Instruction 0x69:" << std::endl << bus.cpu.operationLookup[0x69].instruction_name << std::endl;

    return 0;
}