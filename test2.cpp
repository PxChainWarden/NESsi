#include "Bus.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <bitset>
#include <unistd.h>

int main(){

    Bus bus;


    bus.cpu.write(0x0000,0xA5);
    bus.cpu.write(0x0001,0xF9);
    bus.cpu.write(0x0002,0x38);
    bus.cpu.write(0x0003,0xE5);
    bus.cpu.write(0x0004,0xFF);
    bus.cpu.write(0x00F9,0x80);
    bus.cpu.write(0x00FF,0x01);

    std::string filename = "nestest.nes";
    std::shared_ptr<PxCartridge> cart = std::make_shared<PxCartridge>(filename);
    bus.attachCartridge(cart);

    
    // for(int i = 0x8000; i < 0xC000; i++){
        // std::cout << (unsigned int)bus.cpu.read(i) << std::endl;
    // }
    std::cout << (char)bus.cpu.read(0x8000) << std::endl;

    std::cout << (char)bus.cpu.read(0x8001) << std::endl;
    // printf("Program Counter Starts At: 0x%x\n",bus.cpu.pc);
    // int i = 0;
    // while(i < 3){
    //     printf("\tProgram Counter: 0x%x\n\tEffective Address: 0x%x\n\tAccumulator: 0x%x\n",bus.cpu.pc,bus.cpu.effective_address,bus.cpu.a);
    //     std::cout << "\tStatus Flag: " << std::bitset<8>(bus.cpu.status) << std::endl << std::endl;
    //     bus.cpu.clockByInstruction();
    //     i++;
    // }
    // printf("\tProgram Counter: 0x%x\n\tEffective Address: 0x%x\n\tAccumulator: 0x%x\n",bus.cpu.pc,bus.cpu.effective_address,bus.cpu.a);
    // std::cout << "\tStatus Flag: " << std::bitset<8>(bus.cpu.status) << std::endl << std::endl;
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
    // std::cout << "Status Flag: " << std::bitset<8>(bus.cpu.status) << std::endl;
    // std::cout << std::hex << bus.cpu.a;
    // std::cout << std::hex << (int)bus.cpu.read(0x00FF) << std::endl;
    // std::cout << "Instruction:" << std::endl << bus.cpu.operationLookup[bus.cpu.read(0x00FF)].instruction_name << std::endl;
    return 0;
}