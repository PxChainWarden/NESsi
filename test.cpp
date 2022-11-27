#include "Bus.h"
#include <iostream>
#include <stdio.h>
#include <bitset>

int main(){
    Bus bus;

    // std::cout << std::hex << (int)bus.cpu.read(0x00FF) << std::endl;
    printf("Populate memory manually and call instructions manually for test\n");
    printf("Address 0x0000, Data 0xFF\n");
    printf("Address 0x0001, Data 0xF9\n");
    printf("Address 0x00FF, Data 0x31\n");
    printf("Address 0x00F9, Data 0x69\n");
    bus.cpu.write(0x0000,0xA5);
    bus.cpu.write(0x0001,0xF9);
    bus.cpu.write(0x0002,0xE5);
    bus.cpu.write(0x0003,0xFF);
    bus.cpu.write(0x00F9,0xFF);
    bus.cpu.write(0x00FF,0x7F);
    printf("Program Counter Starts At: 0x%x\n",bus.cpu.pc);
    int i = 0;
    while(i < 10){
        printf("\tProgram Counter: 0x%x\n\tEffective Address: 0x%x\n\tAccumulator: 0x%x\n",bus.cpu.pc,bus.cpu.effective_address,bus.cpu.a);
        std::cout << "Status Flag: " << std::bitset<8>(bus.cpu.status) << std::endl;
        bus.cpu.clock();
        i++;
    }
    // bus.cpu.ZP0();
    // printf("Addressing Mode ZP0 called:\n\tProgram Counter: 0x%x\n\tEffective Address: 0x%x\n\tAccumulator: 0x%x\n",bus.cpu.pc,bus.cpu.effective_address,bus.cpu.a);
    // bus.cpu.LDA();
    // printf("Instruction LDA called:\n\tProgram Counter: 0x%x\n\tEffective Address: 0x%x\n\tAccumulator: 0x%x\n",bus.cpu.pc,bus.cpu.effective_address,bus.cpu.a);
    // bus.cpu.ZP0();
    // printf("Addressing Mode ZP0 called:\n\tProgram Counter: 0x%x\n\tEffective Address: 0x%x\n\tAccumulator: 0x%x\n",bus.cpu.pc,bus.cpu.effective_address,bus.cpu.a);
    // bus.cpu.SBC();
    // printf("Instruction SBC called:\n\tProgram Counter: 0x%x\n\tEffective Address: 0x%x\n\tAccumulator: 0x%x\n",bus.cpu.pc,bus.cpu.effective_address,bus.cpu.a);
    // // printf("After program runs Accumulator should be 0x21, is it correct?\n");
    // std::bitset<8> x(bus.cpu.status);
    std::cout << "Status Flag: " << std::bitset<8>(bus.cpu.status) << std::endl;
    // std::cout << std::hex << bus.cpu.a;
    // std::cout << std::hex << (int)bus.cpu.read(0x00FF) << std::endl;
    // std::cout << "Instruction:" << std::endl << bus.cpu.operationLookup[bus.cpu.read(0x00FF)].instruction_name << std::endl;
    return 0;
}