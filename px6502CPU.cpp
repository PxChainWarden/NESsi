#include "Bus.h"


Px6502CPU::Px6502CPU(/* args */)
{
    // A lookup map for which functions to call to which opcode
    // Map< opcode, Instruction>
    // opcode -> {Instruction Name, Instructuin Function Pointer, Address Mode Function Pointer, Cycle Count}
    operationLookup = {
        // ADD with Carry
        {0x69, {"ADC",&Px6502CPU::ADC,&Px6502CPU::IMM,2}},
        {0x65, {"ADC",&Px6502CPU::ADC,&Px6502CPU::ZP0,3}},
        {0x75, {"ADC",&Px6502CPU::ADC,&Px6502CPU::ZPX,4}},
        {0x6D, {"ADC",&Px6502CPU::ADC,&Px6502CPU::ABS,4}},
        {0x7D, {"ADC",&Px6502CPU::ADC,&Px6502CPU::ABSX,4}},
        {0x79, {"ADC",&Px6502CPU::ADC,&Px6502CPU::ABSY,4}},
        {0x61, {"ADC",&Px6502CPU::ADC,&Px6502CPU::INDX,6}},
        {0x71, {"ADC",&Px6502CPU::ADC,&Px6502CPU::INDY,5}},
        // Logical AND
        {0x29, {"AND",&Px6502CPU::AND,&Px6502CPU::IMM,2}},
        {0x25, {"AND",&Px6502CPU::AND,&Px6502CPU::ZP0,3}},
        {0x35, {"AND",&Px6502CPU::AND,&Px6502CPU::ZPX,4}},
        {0x2D, {"AND",&Px6502CPU::AND,&Px6502CPU::ABS,4}},
        {0x3D, {"AND",&Px6502CPU::AND,&Px6502CPU::ABSX,4}},
        {0x39, {"AND",&Px6502CPU::AND,&Px6502CPU::ABSY,4}},
        {0x21, {"AND",&Px6502CPU::AND,&Px6502CPU::INDX,6}},
        {0x31, {"AND",&Px6502CPU::AND,&Px6502CPU::INDY,5}},
        // Arithmetic Shift Left
        {0x0A, {"ASL",&Px6502CPU::ASL,&Px6502CPU::ACC,2}},
        {0x06, {"ASL",&Px6502CPU::ASL,&Px6502CPU::ZP0,5}},
        {0x16, {"ASL",&Px6502CPU::ASL,&Px6502CPU::ZPX,6}},
        {0x0E, {"ASL",&Px6502CPU::ASL,&Px6502CPU::ABS,6}},
        {0x1E, {"ASL",&Px6502CPU::ASL,&Px6502CPU::ABSX,7}},
        // Branch If Carry Clear
        // TODO Cycle Count calculation
        {0x90, {"BCC",&Px6502CPU::BCC,&Px6502CPU::REL,2}},
        // Branch If Carry Set
        // TODO Cycle Count calculation
        {0xB0, {"BCS",&Px6502CPU::BCS,&Px6502CPU::REL,2}},
        // Branch If Equal
        // TODO Cycle Count calculation
        {0xF0, {"BEQ",&Px6502CPU::BEQ,&Px6502CPU::REL,2}},
        // BIT Test
        {0x24, {"BIT",&Px6502CPU::BIT,&Px6502CPU::ZP0,3}},
        {0x2C, {"BIT",&Px6502CPU::BIT,&Px6502CPU::ABS,4}},
        // Branch If Minus
        // TODO Cycle Count calculation
        {0x30, {"BMI",&Px6502CPU::BMI,&Px6502CPU::REL,2}},
        // Branch If Not Equal
        // TODO Cycle Count calculation
        {0xD0, {"BNE",&Px6502CPU::BNE,&Px6502CPU::REL,2}},
        // Branch If Positive
        // TODO Cycle Count calculation
        {0x10, {"BPL",&Px6502CPU::BPL,&Px6502CPU::REL,2}},
        // Break - Force Interrupt
        {0x00, {"BRK",&Px6502CPU::BRK,&Px6502CPU::IMP,7}},
        // Branch If Overflow Clear
        // TODO Cycle Count calculation
        {0x50, {"BVC",&Px6502CPU::BVC,&Px6502CPU::REL,2}},
        // Branch If Overflow Set
        // TODO Cycle Count calculation
        {0x70, {"BVS",&Px6502CPU::BVS,&Px6502CPU::REL,2}},
        // Clear Carry Flag
        {0x18, {"CLC",&Px6502CPU::CLC,&Px6502CPU::IMP,2}},
        // Clear Decimal Mode
        {0xD8, {"CLD",&Px6502CPU::CLD,&Px6502CPU::IMP,2}},
        // Clear Interrup Disable
        {0x58, {"CLI",&Px6502CPU::CLI,&Px6502CPU::IMP,2}},
        // Clear Overflow Flag
        {0xB8, {"CLV",&Px6502CPU::CLV,&Px6502CPU::IMP,2}},
        // Compare
        {0xC9, {"CMP",&Px6502CPU::CMP,&Px6502CPU::IMM,2}},
        {0xC5, {"CMP",&Px6502CPU::CMP,&Px6502CPU::ZP0,3}},
        {0xD5, {"CMP",&Px6502CPU::CMP,&Px6502CPU::ZPX,4}},
        {0xCD, {"CMP",&Px6502CPU::CMP,&Px6502CPU::ABS,4}},
        {0xDD, {"CMP",&Px6502CPU::CMP,&Px6502CPU::ABSX,4}},
        {0xD9, {"CMP",&Px6502CPU::CMP,&Px6502CPU::ABSY,4}},
        {0xC1, {"CMP",&Px6502CPU::CMP,&Px6502CPU::INDX,6}},
        {0xD1, {"CMP",&Px6502CPU::CMP,&Px6502CPU::INDY,5}},
        // Compare X Register
        {0xE0, {"CPX",&Px6502CPU::CPX,&Px6502CPU::IMM,2}},
        {0xE4, {"CPX",&Px6502CPU::CPX,&Px6502CPU::ZP0,3}},
        {0xEC, {"CPX",&Px6502CPU::CPX,&Px6502CPU::ABS,4}},
        // Compare Y Register
        {0xC0, {"CPY",&Px6502CPU::CPY,&Px6502CPU::IMM,2}},
        {0xC4, {"CPY",&Px6502CPU::CPY,&Px6502CPU::ZP0,3}},
        {0xCC, {"CPY",&Px6502CPU::CPY,&Px6502CPU::ABS,4}},


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

void Px6502CPU::clock(){

}

void Px6502CPU::setFlag(FLAGS flag, bool status){
    if(status){
        status |= flag;             // Set flag in status register. Flag is always 1 on correct bit location. Example (0b01000000)
                                    // Doing an OR operation with flag will always set the flag.
    }else{
        status &= ~flag;            // Clear flag in status register. Flag is always 1 on correct bit location. Example (0b01000000)
                                    // Doint an AND with NOT flag will always clear the flag.
    }
}

uint8_t Px6502CPU::getFlag(FLAGS flag){
    if( (status & flag) > 0)
        return 1;
    return 0;
}

// Accumulator Addressing mode
// The operand A is implicitly defined as the accumulator with a 1 byte instruction.
uint8_t Px6502CPU::ACC(){
    fethced_data = a;
    return 0;
}

// Implied Addressing mode
// The operand is implicitly defined by the instruction.
// Example: INX increment the X register by 1
// No need to do extra things.
uint8_t Px6502CPU::IMP(){
    return 0;
}

// Immediate Addressing mode
// Uses the 8-bit operand itself as the value for the operation, rather than fetching a value from a memory address. 
// So we set the effective address to the operands location. And increase the program counter to continue the process 
uint8_t Px6502CPU::IMM(){
    effective_address = pc;
    pc++;
    return 0;
}

uint8_t Px6502CPU::REL(){

    return 0;
}

// This Addressing mode access data in page 0 in memory. MSB in zero page is $00
// The operand $aa is the LSB of the EA.
// The MSB of the EA is $00. The EA is in the address range $0000-$00FF (zero page).
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf, https://www.nesdev.org/wiki/CPU_addressing_modes
uint8_t Px6502CPU::ZP0(){
    uint8_t operand = read(pc);
    pc++;
    effective_address = (operand) & 0x00FF;     // Mask with page 0
    return 0;
}

// This Addressing mode access data in page 0 in memory with indexed by value of X. MSB in zero page is $00
// The operand $aa is added with no carry (NC) to the index register(X),
// the result $aa + X (NC)is the LSB of the EA. The MSB of the EA is $00. The EA is in zero page.
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf, https://www.nesdev.org/wiki/CPU_addressing_modes
uint8_t Px6502CPU::ZPX(){
    uint8_t operand = read(pc);
    pc++;
    effective_address = (operand + x) & 0x00FF;     // Mask with page 0 (No Carry)
    return 0;
}

// This Addressing mode access data in page 0 in memory with indexed by value of Y. MSB in zero page is $00
// The operand $aa is added with no carry (NC) to the index register(Y),
// the result $aa + Y (NC)is the LSB of the EA. The MSB of the EA is $00. The EA is in zero page.
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf, https://www.nesdev.org/wiki/CPU_addressing_modes
uint8_t Px6502CPU::ZPY(){
    uint8_t operand = read(pc);
    pc++;
    effective_address = (operand + y) & 0x00FF;     // Mask with page 0 (No Carry)
    return 0;
}

// Absolute Addressing mode access the data by 16 bit address.
// The operand $aaaa is the 2 byte effective address (EA).
// The first byte of the operand in machine language is the least significant byte (LSB bits 0-7) of the EA.
// The second byte of the operand in machine language is the most significant byte (MSB bits 8-15) of the EA.
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf, https://www.nesdev.org/wiki/CPU_addressing_modes
uint8_t Px6502CPU::ABS(){
    uint8_t operand_LSB = read(pc);
    pc++;
    uint8_t operand_MSB = read(pc);
    pc++;
    effective_address = (operand_MSB << 8) + operand_LSB;
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
    uint8_t operand_LSB = read(pc);
    pc++;
    uint8_t operand_MSB = read(pc);
    pc++;

    effective_address = ( (operand_MSB << 8) + operand_LSB ) + x;

    if( (effective_address & 0xFF00) != (operand_MSB << 8))
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
    uint8_t operand_LSB = read(pc);
    pc++;
    uint8_t operand_MSB = read(pc);
    pc++;

    effective_address = ( (operand_MSB << 8) + operand_LSB ) + y;

    if( (effective_address & 0xFF00) != (operand_MSB << 8))
        return 1;
    return 0;
}

// Indirect Addressing mode access the data by 16 bit address. Only JMP uses this mode.
// The operand $aaaa contains the LSB of the EA.
// The address $aaaa + $0001 contains the MSB of the EA.
// The 2 byte address (($aaaa + $0001) * $100) + $aaaa contains the EA.
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf, https://www.nesdev.org/wiki/CPU_addressing_modes
uint8_t Px6502CPU::IND(){
    uint8_t operand_LSB = read(pc);
    pc++;
    uint8_t operand_MSB = read(pc);
    pc++;

    effective_address = ( (operand_MSB << 8) + operand_LSB );
    return 0;
}

// Indexed Indirect Addressing mode.
// The operand $aa is added (No Carry) to the X register,
// The result is a zero page address $aa + X (NC) that contains the LSB of the EA.
// The address $aa + X + $01 contains the MSB of the EA.
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf, https://www.nesdev.org/wiki/CPU_addressing_modes
uint8_t Px6502CPU::INDX(){
    uint8_t operand = read(pc);
    pc++;

    uint8_t LSB = read(operand+x);             // No Carry: Addition cant exceed 255 because of LSB being uint8_t
    uint8_t MSB = read(operand+x + 0x01);      // No Carry: Addition cant exceed 255 because of MSB being uint8_t

    effective_address = ( (MSB << 8) + LSB );
    
    return 0;
}

// Indirect Indexed Addressing mode
// The operand $aa is a zero page address, the contents of $aa are added with carry (C) to the Y register
// $aa + Y (C), the result contains the LSB of the EA.
// The contents of address $aa + $01 + C contain the MSB of the EA.
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf, https://www.nesdev.org/wiki/CPU_addressing_modes
uint8_t Px6502CPU::INDY(){
    uint8_t operand = read(pc);
    pc++;

    uint8_t LSB = read(operand);
    uint8_t MSB = read(operand + 0x01);
    

    effective_address = (( MSB << 8) + LSB + y);      // Addition with carry because effective address is 16 bit and y is a 8 bit register.

    return 0;
}

// A function for fetching data after effective address is set by the Addressing Mode
void Px6502CPU::fetch(){
    fethced_data = read(effective_address);
}

// TODO
uint8_t Px6502CPU::ADC(){

    return 0;
}

uint8_t Px6502CPU::AND(){
    fetch();
    a = a & fethced_data;
    if(a == 0x00)
        setFlag(Z,true);
    if( (a & 0b10000000) > 0)
        setFlag(N,true);
    return 0;
}

uint8_t Px6502CPU::ASL(){
    return 0;
}

uint8_t Px6502CPU::BCC(){
    return 0;
}

uint8_t Px6502CPU::BCS(){
    return 0;
}

uint8_t Px6502CPU::BEQ(){
    return 0;
}

uint8_t Px6502CPU::BIT(){
    return 0;
}

uint8_t Px6502CPU::BMI(){
    return 0;
}

uint8_t Px6502CPU::BNE(){
    return 0;
}

uint8_t Px6502CPU::BPL(){
    return 0;
}

uint8_t Px6502CPU::BRK(){
    return 0;
}

uint8_t Px6502CPU::BVC(){
    return 0;
}

uint8_t Px6502CPU::BVS(){
    return 0;
}

uint8_t Px6502CPU::CLC(){
    return 0;
}

uint8_t Px6502CPU::CLD(){
    return 0;
}

uint8_t Px6502CPU::CLI(){
    return 0;
}

uint8_t Px6502CPU::CLV(){
    return 0;
}

uint8_t Px6502CPU::CMP(){
    return 0;
}

uint8_t Px6502CPU::CPX(){
    return 0;
}

uint8_t Px6502CPU::CPY(){
    return 0;
}

uint8_t Px6502CPU::LDA(){
    fetch();
    a = fethced_data;

    if(a == 0x00)                   // Set Zero Flag if loaded data is 0
        setFlag(Z,true);
    if( (a & 0b10000000) > 0)       // Set Negative Flag if bit 7 is set
        setFlag(N,true);

    return 0;
}