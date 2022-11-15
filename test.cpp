#include "Bus.h"
#include <iostream>

int main(){
    Bus bus;

    std::cout << bus.cpu.read(0x1234);

    return 0;
}