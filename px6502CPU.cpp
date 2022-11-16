#include "Bus.h"


Px6502CPU::Px6502CPU(/* args */)
{
    operationLookup = {
        {0x69, {"ADC",&Px6502CPU::ADC,&Px6502CPU::IMM,2}},
        {0x65, {"ADC",&Px6502CPU::ADC,&Px6502CPU::ZP0,3}},
        {0x75, {"ADC",&Px6502CPU::ADC,&Px6502CPU::ZPX,4}},
        {0x6D, {"ADC",&Px6502CPU::ADC,&Px6502CPU::ABS,4}}
    };
}

Px6502CPU::~Px6502CPU()
{
}


uint8_t Px6502CPU::read(uint16_t address){
    return bus->read(address);
}

void Px6502CPU::write(uint16_t address,uint8_t data){
    bus->write(address,data);
}

uint8_t Px6502CPU::IMP(){
    return 0;
}

uint8_t Px6502CPU::IMM(){
    return 0;
}

uint8_t Px6502CPU::REL(){
    return 0;
}

// This Addressing mode access data in page 0 in memory. MSB in zero page is $00
// The operand $aa is the LSB of the EA.
// The MSB of the EA is $00. The EA is in the address range $0000-$00FF (zero page).
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf
uint8_t Px6502CPU::ZP0(){
    effective_address = read(pc);
    pc++;
    effective_address &= 0x00FF;     // Mask with page 0
    return 0;
}

// This Addressing mode access data in page 0 in memory with indexed by value of X. MSB in zero page is $00
// The operand $aa is added with no carry (NC) to the index register(X),
// the result $aa + X (NC)is the LSB of the EA. The MSB of the EA is $00. The EA is in zero page.
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf
uint8_t Px6502CPU::ZPX(){
    effective_address = read(pc + x);
    pc++;
    effective_address &= 0x00FF;     // Mask with page 0 (No Carry)
    return 0;
}

// This Addressing mode access data in page 0 in memory with indexed by value of Y. MSB in zero page is $00
// The operand $aa is added with no carry (NC) to the index register(Y),
// the result $aa + Y (NC)is the LSB of the EA. The MSB of the EA is $00. The EA is in zero page.
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf
uint8_t Px6502CPU::ZPY(){
    effective_address = read(pc + y);
    pc++;
    effective_address &= 0x00FF;     // Mask with page 0 (No Carry)
    return 0;
}

// Absolute Addressing mode access the data by 16 bit address.
// The operand $aaaa is the 2 byte effective address (EA).
// The first byte of the operand in machine language is the least significant byte (LSB bits 0-7) of the EA.
// The second byte of the operand in machine language is the most significant byte (MSB bits 8-15) of the EA.
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf
uint8_t Px6502CPU::ABS(){
    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);
    pc++;
    effective_address = (hi << 8) | lo;
    return 0;
}

// Absolute Addressing mode access the data by 16 bit address indexed by X register.
// The operand $aaaa is the 2 byte effective address (EA).
// The first byte of the operand in machine language is the least significant byte (LSB bits 0-7) of the EA.
// The second byte of the operand in machine language is the most significant byte (MSB bits 8-15) of the EA.
// The operand $aaaa is added to the index register (X), the result $aaaa + X is the EA.
// Warning: This operation can cause additional cycle time if Memory Page is changed. 
// I will return the additional cycle as return value of the function.
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf, https://www.nesdev.org/wiki/CPU_addressing_modes
uint8_t Px6502CPU::ABSX(){
    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);
    pc++;

    effective_address = ( (hi << 8) | lo ) + x;

    if( (effective_address & 0xFF00) != (hi << 8))
        return 1;
    return 0;
}

// Absolute Addressing mode access the data by 16 bit address indexed by Y register.
// The operand $aaaa is the 2 byte effective address (EA).
// The first byte of the operand in machine language is the least significant byte (LSB bits 0-7) of the EA.
// The second byte of the operand in machine language is the most significant byte (MSB bits 8-15) of the EA.
// The operand $aaaa is added to the index register (Y), the result $aaaa + Y is the EA.
// Warning: This operation can cause additional cycle time if Memory Page is changed. 
// I will return the additional cycle as return value of the function.
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf, https://www.nesdev.org/wiki/CPU_addressing_modes
uint8_t Px6502CPU::ABSY(){
    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);
    pc++;

    effective_address = ( (hi << 8) | lo ) + y;

    if( (effective_address & 0xFF00) != (hi << 8))
        return 1;
    return 0;
}

// Indirect Addressing mode access the data by 16 bit address. Only JMP uses this mode.
// The operand $aaaa contains the LSB of the EA.
// The address $aaaa + $0001 contains the MSB of the EA.
// The 2 byte address (($aaaa + $0001) * $100) + $aaaa contains the EA.
uint8_t Px6502CPU::IND(){
    uint8_t lo = read(pc);
    pc++;
    uint8_t hi = read(pc);
    pc++;

    effective_address = ( (hi << 8) | lo );
    return 0;
}

uint8_t Px6502CPU::INDX(){
    return 0;
}

uint8_t Px6502CPU::INDY(){
    return 0;
}

// A function for fetching data after effective address is set by the Addressing Mode
void Px6502CPU::fetch(){
}

// TODO
uint8_t Px6502CPU::ADC(){
    return 0;
}

uint8_t Px6502CPU::AND(){
    return 0;
}