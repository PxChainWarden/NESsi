#include "Bus.h"

Bus::Bus(/* args */)
{
    this->cpu.connectBus(this);

    for(auto &i : this->memory)
        i = 0x00;
}

Bus::~Bus()
{
}

uint8_t Bus::read(uint16_t address){
    if(address <= 0xFFFF && address >= 0x0000)
        return this->memory[address];
    return 0x00;
}

void Bus::write(uint16_t address, uint8_t data){
    if(address <= 0xFFFF && address >= 0x0000)
        this->memory[address] = data;
}