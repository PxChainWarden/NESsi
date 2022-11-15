#include "Bus.h"


Px6502CPU::Px6502CPU(/* args */)
{
    // this->operations = {
    //     {"ADC",}
    // };
}

Px6502CPU::~Px6502CPU()
{
}


uint8_t Px6502CPU::read(uint16_t address){
    return (this->bus)->read(address);
}

void Px6502CPU::write(uint16_t address,uint8_t data){
    (this->bus)->write(address,data);
}


uint8_t Px6502CPU::ZP0(){
    this->memory_address = read(this->pc);
    this->pc++;
    this->memory_address &= 0x00FF;     // Mask with page 0
    return 0;
}

uint8_t Px6502CPU::ZPX(){
    this->memory_address = read(this->pc + this->x);
    this->pc++;
    this->memory_address &= 0x00FF;     // Mask with page 0
    return 0;
}

uint8_t Px6502CPU::ZPY(){
    this->memory_address = read(this->pc + this->y);
    this->pc++;
    this->memory_address &= 0x00FF;     // Mask with page 0
    return 0;
}