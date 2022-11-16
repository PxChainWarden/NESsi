#include "Bus.h"
#include <iostream>

int main(){
    Bus bus;

    std::cout << std::hex << (int)bus.cpu.read(0x1234) << std::endl;

    std::cout << std::hex << (int)bus.cpu.read(0x00FF) << std::endl;
    bus.cpu.write(0x00FF,0xA1);
    std::cout << std::hex << (int)bus.cpu.read(0x00FF) << std::endl;

    return 0;
}