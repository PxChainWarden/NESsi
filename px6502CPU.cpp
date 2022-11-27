#include "Bus.h"
#include <iostream>

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
        // Decrement Memory
        {0xC6, {"DEC",&Px6502CPU::DEC,&Px6502CPU::ZP0,5}},
        {0xD6, {"DEC",&Px6502CPU::DEC,&Px6502CPU::ZPX,6}},
        {0xCE, {"DEC",&Px6502CPU::DEC,&Px6502CPU::ABS,6}},
        {0xDE, {"DEC",&Px6502CPU::DEC,&Px6502CPU::ABSX,7}},
        // Decrement X Register
        {0xCA, {"DEX",&Px6502CPU::DEX,&Px6502CPU::IMP,2}},
        // Decrement Y Register
        {0x88, {"DEY",&Px6502CPU::DEY,&Px6502CPU::IMP,2}},
        // Exclusive OR
        {0x49, {"EOR",&Px6502CPU::EOR,&Px6502CPU::IMM,2}},
        {0x45, {"EOR",&Px6502CPU::EOR,&Px6502CPU::ZP0,3}},
        {0x55, {"EOR",&Px6502CPU::EOR,&Px6502CPU::ZPX,4}},
        {0x4D, {"EOR",&Px6502CPU::EOR,&Px6502CPU::ABS,4}},
        {0x5D, {"EOR",&Px6502CPU::EOR,&Px6502CPU::ABSX,4}},
        {0x59, {"EOR",&Px6502CPU::EOR,&Px6502CPU::ABSY,4}},
        {0x41, {"EOR",&Px6502CPU::EOR,&Px6502CPU::INDX,6}},
        {0x51, {"EOR",&Px6502CPU::EOR,&Px6502CPU::INDY,5}},
        // Increment Memory
        {0xE6, {"INC",&Px6502CPU::INC,&Px6502CPU::ZP0,5}},
        {0xF6, {"INC",&Px6502CPU::INC,&Px6502CPU::ZPX,6}},
        {0xEE, {"INC",&Px6502CPU::INC,&Px6502CPU::ABS,6}},
        {0xFE, {"INC",&Px6502CPU::INC,&Px6502CPU::ABSX,7}},
        // Increment X Register
        {0xE8, {"INX",&Px6502CPU::INX,&Px6502CPU::IMP,2}},
        // Increment Y Register
        {0xC8, {"INY",&Px6502CPU::INY,&Px6502CPU::IMP,2}},
        // Jump
        {0x4C, {"JMP",&Px6502CPU::JMP,&Px6502CPU::ABS,3}},
        {0x6C, {"JMP",&Px6502CPU::JMP,&Px6502CPU::IND,5}},
        // Jump Subroutine
        {0x20, {"JSR",&Px6502CPU::JSR,&Px6502CPU::ABS,6}},
        // Load Accumulator
        {0xA9, {"LDA",&Px6502CPU::LDA,&Px6502CPU::IMM,2}},
        {0xA5, {"LDA",&Px6502CPU::LDA,&Px6502CPU::ZP0,3}},
        {0xB5, {"LDA",&Px6502CPU::LDA,&Px6502CPU::ZPX,4}},
        {0xAD, {"LDA",&Px6502CPU::LDA,&Px6502CPU::ABS,4}},
        {0xBD, {"LDA",&Px6502CPU::LDA,&Px6502CPU::ABSX,4}},
        {0xB9, {"LDA",&Px6502CPU::LDA,&Px6502CPU::ABSY,4}},
        {0xA1, {"LDA",&Px6502CPU::LDA,&Px6502CPU::INDX,6}},
        {0xB1, {"LDA",&Px6502CPU::LDA,&Px6502CPU::INDY,5}},
        // Load X Register
        {0xA2, {"LDX",&Px6502CPU::LDX,&Px6502CPU::IMM,2}},
        {0xA6, {"LDX",&Px6502CPU::LDX,&Px6502CPU::ZP0,3}},
        {0xB6, {"LDX",&Px6502CPU::LDX,&Px6502CPU::ZPY,4}},
        {0xAE, {"LDX",&Px6502CPU::LDX,&Px6502CPU::ABS,4}},
        {0xBE, {"LDX",&Px6502CPU::LDX,&Px6502CPU::ABSY,4}},
        // Load Y Register
        {0xA2, {"LDY",&Px6502CPU::LDY,&Px6502CPU::IMM,2}},
        {0xA6, {"LDY",&Px6502CPU::LDY,&Px6502CPU::ZP0,3}},
        {0xB6, {"LDY",&Px6502CPU::LDY,&Px6502CPU::ZPX,4}},
        {0xAE, {"LDY",&Px6502CPU::LDY,&Px6502CPU::ABS,4}},
        {0xBE, {"LDY",&Px6502CPU::LDY,&Px6502CPU::ABSX,4}},
        // Logical Shift Right
        {0x4A, {"LSR",&Px6502CPU::LSR,&Px6502CPU::ACC,2}},
        {0x46, {"LSR",&Px6502CPU::LSR,&Px6502CPU::ZP0,5}},
        {0x56, {"LSR",&Px6502CPU::LSR,&Px6502CPU::ZPX,6}},
        {0x4E, {"LSR",&Px6502CPU::LSR,&Px6502CPU::ABS,6}},
        {0x5E, {"LSR",&Px6502CPU::LSR,&Px6502CPU::ABSX,7}},
        // No Operation
        {0xEA, {"NOP",&Px6502CPU::NOP,&Px6502CPU::IMP,2}},
        // Logical Inclusive OR
        {0x09, {"ORA",&Px6502CPU::ORA,&Px6502CPU::IMM,2}},
        {0x05, {"ORA",&Px6502CPU::ORA,&Px6502CPU::ZP0,3}},
        {0x15, {"ORA",&Px6502CPU::ORA,&Px6502CPU::ZPX,4}},
        {0x0D, {"ORA",&Px6502CPU::ORA,&Px6502CPU::ABS,4}},
        {0x1D, {"ORA",&Px6502CPU::ORA,&Px6502CPU::ABSX,4}},
        {0x19, {"ORA",&Px6502CPU::ORA,&Px6502CPU::ABSY,4}},
        {0x01, {"ORA",&Px6502CPU::ORA,&Px6502CPU::INDX,6}},
        {0x11, {"ORA",&Px6502CPU::ORA,&Px6502CPU::INDY,5}},
        // Push Accumulator
        {0x48, {"PHA",&Px6502CPU::PHA,&Px6502CPU::IMP,3}},
        // Push Processor Status
        {0x08, {"PHP",&Px6502CPU::PHP,&Px6502CPU::IMP,3}},
        // Pull Accumulator
        {0x68, {"PLA",&Px6502CPU::PLA,&Px6502CPU::IMP,4}},
        // Pull Processor Status
        {0x28, {"PLP",&Px6502CPU::PLP,&Px6502CPU::IMP,4}},
        // Rotate Left
        {0x2A, {"ROL",&Px6502CPU::ROL,&Px6502CPU::ACC,2}},
        {0x26, {"ROL",&Px6502CPU::ROL,&Px6502CPU::ZP0,5}},
        {0x36, {"ROL",&Px6502CPU::ROL,&Px6502CPU::ZPX,6}},
        {0x2E, {"ROL",&Px6502CPU::ROL,&Px6502CPU::ABS,6}},
        {0x3E, {"ROL",&Px6502CPU::ROL,&Px6502CPU::ABSX,7}},
        // Rotate Right
        {0x6A, {"ROR",&Px6502CPU::ROR,&Px6502CPU::ACC,2}},
        {0x66, {"ROR",&Px6502CPU::ROR,&Px6502CPU::ZP0,5}},
        {0x76, {"ROR",&Px6502CPU::ROR,&Px6502CPU::ZPX,6}},
        {0x6E, {"ROR",&Px6502CPU::ROR,&Px6502CPU::ABS,6}},
        {0x7E, {"ROR",&Px6502CPU::ROR,&Px6502CPU::ABSX,7}},
        // Return from Interrupt
        {0x40, {"RTI",&Px6502CPU::RTI,&Px6502CPU::IMP,6}},
        // Return from Subroutine
        {0x60, {"RTS",&Px6502CPU::RTS,&Px6502CPU::IMP,6}},
        // Substract with Carry
        {0xE9, {"SBC",&Px6502CPU::SBC,&Px6502CPU::IMM,2}},
        {0xE5, {"SBC",&Px6502CPU::SBC,&Px6502CPU::ZP0,3}},
        {0xF5, {"SBC",&Px6502CPU::SBC,&Px6502CPU::ZPX,4}},
        {0xED, {"SBC",&Px6502CPU::SBC,&Px6502CPU::ABS,4}},
        {0xFD, {"SBC",&Px6502CPU::SBC,&Px6502CPU::ABSX,4}},
        {0xF9, {"SBC",&Px6502CPU::SBC,&Px6502CPU::ABSY,4}},
        {0xE1, {"SBC",&Px6502CPU::SBC,&Px6502CPU::INDX,6}},
        {0xF1, {"SBC",&Px6502CPU::SBC,&Px6502CPU::INDY,5}},
        // Set Carry Flag
        {0x38, {"SEC",&Px6502CPU::SEC,&Px6502CPU::IMP,2}},
        // Set Decimal Flag
        {0xF8, {"SED",&Px6502CPU::SED,&Px6502CPU::IMP,2}},
        // Set Interrupt Disable
        {0x78, {"SEI",&Px6502CPU::SEI,&Px6502CPU::IMP,2}},
        // Store Accumulator
        {0x85, {"STA",&Px6502CPU::STA,&Px6502CPU::ZP0,3}},
        {0x95, {"STA",&Px6502CPU::STA,&Px6502CPU::ZPX,4}},
        {0x8D, {"STA",&Px6502CPU::STA,&Px6502CPU::ABS,4}},
        {0x9D, {"STA",&Px6502CPU::STA,&Px6502CPU::ABSX,5}},
        {0x99, {"STA",&Px6502CPU::STA,&Px6502CPU::ABSY,5}},
        {0x81, {"STA",&Px6502CPU::STA,&Px6502CPU::INDX,6}},
        {0x91, {"STA",&Px6502CPU::STA,&Px6502CPU::INDY,6}},
        // Store X Register
        {0x89, {"STX",&Px6502CPU::STX,&Px6502CPU::ZP0,3}},
        {0x96, {"STX",&Px6502CPU::STX,&Px6502CPU::ZPY,4}},
        {0x8E, {"STX",&Px6502CPU::STX,&Px6502CPU::ABS,4}},
        // Store Y Register
        {0x84, {"STY",&Px6502CPU::STY,&Px6502CPU::ZP0,3}},
        {0x94, {"STY",&Px6502CPU::STY,&Px6502CPU::ZPX,4}},
        {0x8C, {"STY",&Px6502CPU::STY,&Px6502CPU::ABS,4}},
        // Transfer Accumulator to Register X
        {0xAA, {"TAX",&Px6502CPU::TAX,&Px6502CPU::IMP,2}},
        // Transfer Accumulator to Register Y
        {0xA8, {"TAY",&Px6502CPU::TAY,&Px6502CPU::IMP,2}},
        // Transfer Stack Pointer to Register X
        {0xBA, {"TSX",&Px6502CPU::TSX,&Px6502CPU::IMP,2}},
        // Transfer X Register to Accumulator
        {0x8A, {"TXA",&Px6502CPU::TXA,&Px6502CPU::IMP,2}},
        // Transfer X Register to Stack Pointer
        {0x9A, {"TXS",&Px6502CPU::TXS,&Px6502CPU::IMP,2}},
        // Transfer Y Register to Accumulator
        {0x98, {"TYA",&Px6502CPU::TYA,&Px6502CPU::IMP,2}},
    };
}

Px6502CPU::~Px6502CPU()
{
}

// A Read Memory function for CPU.
// If addressing mode is Accumulator it returns the accumulator
// Else returns the data at given address 
uint8_t Px6502CPU::read(uint16_t address){
        return bus->read(address);
}

// A Write Memory function for CPU
void Px6502CPU::write(uint16_t address,uint8_t data){
    bus->write(address,data);
}

void Px6502CPU::clock(){
    if(cycles == 0){
        opcode = read(pc);
        pc++;
        cycles = operationLookup[opcode].cycles;

        cycles += (this->*operationLookup[opcode].pAddressingFunction)();
        cycles += (this->*operationLookup[opcode].pOperationFunction)();
    }

    cycles--;

}

void Px6502CPU::clockByInstruction(){
    do{
        clock();
    }
    while(cycles > 0);
}

void Px6502CPU::setFlag(FLAGS flag, bool s){
    if(s){
        // std::cout << s << std::endl << flag << std::endl;
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

// =========================================== ADDRESSING MODES ===========================================
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
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf, https://www.nesdev.org/wiki/CPU_addressing_modes 
uint8_t Px6502CPU::IMM(){
    effective_address = pc;
    pc++;
    return 0;
}

// Relative Addressing mode
// The operand $aa is added to the LSB of the PC as an offset, with a range of $-80 to $+7F.
// Source: https://slark.me/c64-downloads/6502-addressing-modes.pdf, https://www.nesdev.org/wiki/CPU_addressing_modes
uint8_t Px6502CPU::REL(){
    // Using Signed Integer as relative addressing.
    int8_t operand = read(pc);
    pc++;
    relative_address = operand;
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

    if( (effective_address & 0xFF00) != (operand_MSB << 8))             // return additional cycle count if memory page is changed
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

    if( (effective_address & 0xFF00) != (operand_MSB << 8))             // return additional cycle count if memory page is changed
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
    

    effective_address = (( MSB << 8) + LSB + y);        // Addition with carry because effective address is 16 bit and y is a 8 bit register.

    if( (effective_address & 0xFF00) != (MSB << 8) )    // return additional cycle count if memory page is changed
        return 1;                                       
    return 0;
}

// A function for fetching data after effective address is set by the Addressing Mode
uint8_t Px6502CPU::fetch(){
    if( operationLookup[opcode].pAddressingFunction != &Px6502CPU::IMP )
        return read(effective_address);
    return 0x00;
}

// =========================================== INSTRUCTIONS ===========================================
// Instruction Set for MOS 6502 CPU
// More details can be found here: https://www.nesdev.org/obelisk-6502-guide/reference.html

// Adding with carry
// More Details: https://teaching.idallen.com/dat2343/10f/notes/040_overflow.txt
uint8_t Px6502CPU::ADC(){
    fethced_data = read(effective_address);

    uint8_t temp = a + fethced_data + getFlag(C);

    bool accumulatorSignBit = a & (0b10000000);                 // Get Bit 7 of the Accumulator
    bool fethedDataSignBit = fethced_data & (0b10000000);       // Get Bit 7 of the Fetched Memory Data

    bool tempDataSignBit = temp & (0b10000000);                 // Get Bit 7 of the Addition

    // Set Overflow Truth Table

    // fethedDataSignBit | accumulatorSignBit | tempDataSignBit |  Overflow Status
    //        0          |          0         |         0       |         0
    //        0          |          0         |         1       |         1
    //        0          |          1         |         0       |         0
    //        0          |          1         |         1       |         0
    //        1          |          0         |         0       |         0
    //        1          |          0         |         1       |         0
    //        1          |          1         |         0       |         1
    //        1          |          1         |         1       |         0
    setFlag(V, (fethedDataSignBit == accumulatorSignBit) and (tempDataSignBit != accumulatorSignBit) );

    setFlag(C, temp < (a + fethced_data));

    a = temp;
    
    setFlag(N, (a & 0b10000000) > 0);
    setFlag(Z, a == 0x00);

    return 0;
}

uint8_t Px6502CPU::AND(){
    a = a & read(effective_address);
    setFlag(Z, a == 0x00);
    setFlag(N,(a & 0b10000000) > 0);
    return 0;
}

uint8_t Px6502CPU::ASL(){
    // Read data from memory if addressing mode is not accumulator.
    // Accumulator addressing mode function will set fetched data to value of Accumulator.
    if(operationLookup[opcode].pAddressingFunction != &Px6502CPU::ACC)
        fethced_data = read(effective_address);
    else
        fethced_data = a;
    
    setFlag(C,fethced_data & 0b10000000);             // Set Carry Flag to the Bit 7 of the Data
    
    uint8_t temp = fethced_data << 1;
    setFlag(Z, temp == 0x00);                                  // Set Zero Flag if loaded data after operation is 0
    setFlag(N, (temp & 0b10000000) > 0);                       // Set Negative Flag if bit 7 is set

    if(operationLookup[opcode].pAddressingFunction == &Px6502CPU::ACC)
        a = temp;
    else
        write(effective_address,temp);

    return 0;
}

uint8_t Px6502CPU::BCC(){
    if(getFlag(C) == 0x00){
        uint16_t newProgramCounter = pc + relative_address;
        if( (pc & 0xFF00) != (newProgramCounter & 0xFF00) ){
            pc = newProgramCounter;
            return 2;
        }
        pc = newProgramCounter;
        return 1;
    }
    return 0;
}

uint8_t Px6502CPU::BCS(){
    if(getFlag(C) > 0){
        uint16_t newProgramCounter = pc + relative_address;
        if( (pc & 0xFF00) != (newProgramCounter & 0xFF00) ){
            pc = newProgramCounter;
            return 2;
        }
        pc = newProgramCounter;
        return 1;
    }
    return 0;
}

uint8_t Px6502CPU::BEQ(){
    if(getFlag(Z) > 0){
        uint16_t newProgramCounter = pc + relative_address;
        if( (pc & 0xFF00) != (newProgramCounter & 0xFF00) ){
            pc = newProgramCounter;
            return 2;
        }
        pc = newProgramCounter;
        return 1;
    }
    return 0;
}

uint8_t Px6502CPU::BIT(){
    fethced_data = read(effective_address);
    uint8_t temp = a & fethced_data;
    setFlag(Z, temp == 0x00);
    setFlag(N,(fethced_data & 0b10000000) > 0);
    setFlag(V,(fethced_data & 0b01000000) > 0);
    return 0;
}

uint8_t Px6502CPU::BMI(){
    if(getFlag(N) > 0){
        uint16_t newProgramCounter = pc + relative_address;
        if( (pc & 0xFF00) != (newProgramCounter & 0xFF00) ){
            pc = newProgramCounter;
            return 2;
        }
        pc = newProgramCounter;
        return 1;
    }
    return 0;
}

uint8_t Px6502CPU::BNE(){
    if(getFlag(Z) == 0){
        uint16_t newProgramCounter = pc + relative_address;
        if( (pc & 0xFF00) != (newProgramCounter & 0xFF00) ){
            pc = newProgramCounter;
            return 2;
        }
        pc = newProgramCounter;
        return 1;
    }
    return 0;
}

uint8_t Px6502CPU::BPL(){
    if(getFlag(N) == 0){
        uint16_t newProgramCounter = pc + relative_address;
        if( (pc & 0xFF00) != (newProgramCounter & 0xFF00) ){
            pc = newProgramCounter;
            return 2;
        }
        pc = newProgramCounter;
        return 1;
    }
    return 0;
}

uint8_t Px6502CPU::BRK(){
    uint8_t MSB = pc >> 8;
    uint8_t LSB = pc & 0x00FF;

    setFlag(B,true);

    write(0x0100 + sp, MSB);
    sp--;
    write(0x0100 + sp, LSB);
    sp--;

    write(0x0100 + sp, status);
    sp--;

    LSB = read(0xFFFE);
    MSB = read(0xFFFF);

    pc = (MSB << 8) + LSB; 

    return 0;
}

uint8_t Px6502CPU::BVC(){
    if(getFlag(V) == 0){
        uint16_t newProgramCounter = pc + relative_address;
        if( (pc & 0xFF00) != (newProgramCounter & 0xFF00) ){
            pc = newProgramCounter;
            return 2;
        }
        pc = newProgramCounter;
        return 1;
    }
    return 0;
}

uint8_t Px6502CPU::BVS(){
    if(getFlag(V) > 0){
        uint16_t newProgramCounter = pc + relative_address;
        if( (pc & 0xFF00) != (newProgramCounter & 0xFF00) ){
            pc = newProgramCounter;
            return 2;
        }
        pc = newProgramCounter;
        return 1;
    }
    return 0;
}

uint8_t Px6502CPU::CLC(){
    setFlag(C,false);
    return 0;
}

uint8_t Px6502CPU::CLD(){
    setFlag(D,false);
    return 0;
}

uint8_t Px6502CPU::CLI(){
    setFlag(I,false);
    return 0;
}

uint8_t Px6502CPU::CLV(){
    setFlag(V,false);
    return 0;
}

uint8_t Px6502CPU::CMP(){
    uint8_t compare = a - read(effective_address);
    setFlag(Z, compare == 0x00);                  // Set Zero Flag if loaded data is 0
    setFlag(N, (compare & 0b10000000) > 0);       // Set Negative Flag if bit 7 is set
    setFlag(C, a >= read(effective_address));     // Set Carry Flag if Accumulator is greater than Memory Data
    return 0;
}

uint8_t Px6502CPU::CPX(){
    uint8_t compare = x - read(effective_address);
    setFlag(Z, compare == 0x00);                  // Set Zero Flag if loaded data is 0
    setFlag(N, (compare & 0b10000000) > 0);       // Set Negative Flag if bit 7 is set
    setFlag(C, x >= read(effective_address));     // Set Carry Flag if X Register is greater than Memory Data
    return 0;
}

uint8_t Px6502CPU::CPY(){
    uint8_t compare = y - read(effective_address);
    setFlag(Z, compare == 0x00);                  // Set Zero Flag if loaded data is 0
    setFlag(N, (compare & 0b10000000) > 0);       // Set Negative Flag if bit 7 is set
    setFlag(C, y >= read(effective_address));     // Set Carry Flag if Y Register is greater than Memory Data
    return 0;
}

uint8_t Px6502CPU::DEC(){
    fethced_data = read(effective_address);
    fethced_data--;
    write(effective_address,fethced_data);
    setFlag(Z, fethced_data == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (fethced_data & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}

uint8_t Px6502CPU::DEX(){
    x--;
    setFlag(Z, x == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (x & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}

uint8_t Px6502CPU::DEY(){
    y--;
    setFlag(Z, y == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (y & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}

uint8_t Px6502CPU::EOR(){
    a = a ^ read(effective_address);
    setFlag(Z, a == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (a & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}

uint8_t Px6502CPU::INC(){
    fethced_data = read(effective_address);
    fethced_data++;
    write(effective_address,fethced_data);
    setFlag(Z, fethced_data == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (fethced_data & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}

uint8_t Px6502CPU::INX(){
    x++;
    setFlag(Z, x == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (x & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}

uint8_t Px6502CPU::INY(){
    y++;
    setFlag(Z, y == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (y & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}

uint8_t Px6502CPU::JMP(){
    pc = effective_address;
    return 0;
}

uint8_t Px6502CPU::JSR(){
    pc--;
    // Everyting in page 1 is considered stack in 6502.
    // Store Program Counter to Stack. MSB first
    uint8_t MSB = pc >> 8;
    uint8_t LSB = pc & 0x00FF;

    write(0x0100 + sp, MSB);
    sp--;
    write(0x0100 + sp, LSB);
    sp--;

    pc = effective_address;
    return 0;
}

uint8_t Px6502CPU::LDA(){
    a = read(effective_address);

    setFlag(Z, a == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (a & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set

    return 0;
}

uint8_t Px6502CPU::LDX(){
    x = read(effective_address);

    setFlag(Z, x == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (x & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set

    return 0;
}

uint8_t Px6502CPU::LDY(){
    y = read(effective_address);

    setFlag(Z, y == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N,  (y & 0b10000000) > 0);       // Set Negative Flag if bit 7 is set

    return 0;
}

uint8_t Px6502CPU::LSR(){
    // Read data from memory if addressing mode is not accumulator.
    // Accumulator addressing mode function will set fetched data to value of Accumulator.
    if(operationLookup[opcode].pAddressingFunction != &Px6502CPU::ACC)
        fethced_data = read(effective_address);
    else
        fethced_data = a;
    
    setFlag(C,fethced_data & 0b00000001);             // Set Carry Flag to the Bit 0 of the Data
    
    uint8_t temp = fethced_data >> 1;
    setFlag(Z, temp == 0x00);                                  // Set Zero Flag if loaded data is 0
    setFlag(N, (temp & 0b10000000) > 0);                       // Set Negative Flag if bit 7 is set

    if(operationLookup[opcode].pAddressingFunction == &Px6502CPU::ACC)
        a = temp;
    else
        write(effective_address,temp);

    return 0;
}

uint8_t Px6502CPU::NOP(){
    return 0;
}

uint8_t Px6502CPU::ORA(){
    a = a | read(effective_address);
    setFlag(Z, a == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (a & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}

uint8_t Px6502CPU::PHA(){
    write(0x0100 + sp, a);
    sp--;
    return 0;
}

uint8_t Px6502CPU::PHP(){
    write(0x0100 + sp, status);
    sp--;
    return 0;
}

uint8_t Px6502CPU::PLA(){
    sp++;
    a = read(0x0100 + sp);
    setFlag(Z, a == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (a & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}

uint8_t Px6502CPU::PLP(){
    sp++;
    status = read(0x0100 + sp);
    return 0;
}

// TODO Maybe needs a fix
uint8_t Px6502CPU::ROL(){
    // Read data from memory if addressing mode is not accumulator.
    // Accumulator addressing mode function will set fetched data to value of Accumulator.
    if(operationLookup[opcode].pAddressingFunction != &Px6502CPU::ACC)
        fethced_data = read(effective_address);
    else
        fethced_data = a;

    uint8_t temp = fethced_data << 1;
    temp += getFlag(C) > 0 ? 1 : 0;
    
    setFlag(C,fethced_data & 0b10000000);             // Set Carry Flag to the Bit 7 of the Data
    
    
    setFlag(Z, temp == 0x00);                                  // Set Zero Flag if loaded data is 0
    setFlag(N, (temp & 0b10000000) > 0);                       // Set Negative Flag if bit 7 is set
    if(operationLookup[opcode].pAddressingFunction == &Px6502CPU::ACC)
        a = temp;
    else
        write(effective_address,temp);
    return 0;
}

uint8_t Px6502CPU::ROR(){
    // Read data from memory if addressing mode is not accumulator.
    // Accumulator addressing mode function will set fetched data to value of Accumulator.
    if(operationLookup[opcode].pAddressingFunction != &Px6502CPU::ACC)
        fethced_data = read(effective_address);
    else
        fethced_data = a;

    uint8_t temp = fethced_data >> 1;
    temp += getFlag(C) > 0 ? 128 : 0;
    
    setFlag(C,fethced_data & 0b00000001);             // Set Carry Flag to the Bit 7 of the Data
    
    
    setFlag(Z, temp == 0x00);                                  // Set Zero Flag if loaded data is 0
    setFlag(N, (temp & 0b10000000) > 0);                       // Set Negative Flag if bit 7 is set
    if(operationLookup[opcode].pAddressingFunction == &Px6502CPU::ACC)
        a = temp;
    else
        write(effective_address,temp);
    return 0;
}

uint8_t Px6502CPU::RTI(){
    setFlag(B,false);
    
    sp++;
    status = read(0x0100 + sp);
    sp++;
    uint8_t LSB = read(0x0100 + sp);
    sp++;
    uint8_t MSB  = read(0x0100 + sp);

    pc = (MSB << 8) + LSB; 

    return 0;
}

uint8_t Px6502CPU::RTS(){
    // Everyting in page 1 is considered stack in 6502.
    // Read the stored Program Counter from Stack. LSB first

    sp++;
    uint8_t LSB = read(0x0100 + sp);
    sp++;
    uint8_t MSB = read(0x0100 + sp);

    pc = (MSB << 8) + LSB - 1;
    return 0;
}

uint8_t Px6502CPU::SBC(){
    fethced_data = read(effective_address);
    uint8_t temp = a - fethced_data - (1 - getFlag(C));

    bool accumulatorSignBit = a & (0b10000000);                 // Get Bit 7 of the Accumulator
    bool fethedDataSignBit = fethced_data & (0b10000000);       // Get Bit 7 of the Fetched Memory Data

    bool tempDataSignBit = temp & (0b10000000);                 // Get Bit 7 of the Addition

    // Set Overflow Truth Table for Substract

    // fethedDataSignBit | accumulatorSignBit | tempDataSignBit |  Overflow Status
    //        0          |          0         |         0       |         0
    //        0          |          0         |         1       |         0
    //        0          |          1         |         0       |         0
    //        0          |          1         |         1       |         1
    //        1          |          0         |         0       |         1
    //        1          |          0         |         1       |         0
    //        1          |          1         |         0       |         0
    //        1          |          1         |         1       |         0
    setFlag(V, (fethedDataSignBit != accumulatorSignBit) and (tempDataSignBit == accumulatorSignBit) );

    setFlag(C, temp > (a + fethced_data));

    a = temp;
    
    setFlag(N, (a & 0b10000000) > 0);
    setFlag(Z, a == 0x00);

    return 0;
}

uint8_t Px6502CPU::SEC(){
    setFlag(C,true);
    return 0;
}

uint8_t Px6502CPU::SED(){
    setFlag(D,true);
    return 0;
}

uint8_t Px6502CPU::SEI(){
    setFlag(I,true);
    return 0;
}

uint8_t Px6502CPU::STA(){
    write(effective_address,a);
    return 0;
}

uint8_t Px6502CPU::STX(){
    write(effective_address,x);
    return 0;
}

uint8_t Px6502CPU::STY(){
    write(effective_address,y);
    return 0;
}

uint8_t Px6502CPU::TAX(){
    x = a;
    setFlag(Z, x == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (x & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}

uint8_t Px6502CPU::TAY(){
    y = a;
    setFlag(Z, y == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (y & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}

uint8_t Px6502CPU::TSX(){
    x = sp;
    setFlag(Z, x == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (x & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}

uint8_t Px6502CPU::TXA(){
    a = x;
    setFlag(Z, a == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (a & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}

uint8_t Px6502CPU::TXS(){
    sp = x;
    return 0;
}

uint8_t Px6502CPU::TYA(){
    a = y;
    setFlag(Z, a == 0x00);                   // Set Zero Flag if loaded data is 0
    setFlag(N, (a & 0b10000000) > 0);        // Set Negative Flag if bit 7 is set
    return 0;
}
