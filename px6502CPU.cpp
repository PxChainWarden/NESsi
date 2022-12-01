#include "Bus.h"
#include <iostream>

Px6502CPU::Px6502CPU(/* args */)
{
    // A lookup map for which functions to call to which opcode
    // Map< opcode, Instruction>
    // opcode -> {Instruction Name, Instructuin Function Pointer, Address Mode Function Pointer, Cycle Count}
    operationLookup = {
            // ADD with Carry
            {0x69, {"ADC",&Px6502CPU::ADC,&Px6502CPU::IMM,2,false}},
            {0x65, {"ADC",&Px6502CPU::ADC,&Px6502CPU::ZP0,3,false}},
            {0x75, {"ADC",&Px6502CPU::ADC,&Px6502CPU::ZPX,4,false}},
            {0x6D, {"ADC",&Px6502CPU::ADC,&Px6502CPU::ABS,4,false}},
            {0x7D, {"ADC",&Px6502CPU::ADC,&Px6502CPU::ABSX,4,true}},
            {0x79, {"ADC",&Px6502CPU::ADC,&Px6502CPU::ABSY,4,true}},
            {0x61, {"ADC",&Px6502CPU::ADC,&Px6502CPU::INDX,6,false}},
            {0x71, {"ADC",&Px6502CPU::ADC,&Px6502CPU::INDY,5,true}},
            // Logical AND
            {0x29, {"AND",&Px6502CPU::AND,&Px6502CPU::IMM,2,false}},
            {0x25, {"AND",&Px6502CPU::AND,&Px6502CPU::ZP0,3,false}},
            {0x35, {"AND",&Px6502CPU::AND,&Px6502CPU::ZPX,4,false}},
            {0x2D, {"AND",&Px6502CPU::AND,&Px6502CPU::ABS,4,false}},
            {0x3D, {"AND",&Px6502CPU::AND,&Px6502CPU::ABSX,4,true}},
            {0x39, {"AND",&Px6502CPU::AND,&Px6502CPU::ABSY,4,true}},
            {0x21, {"AND",&Px6502CPU::AND,&Px6502CPU::INDX,6,false}},
            {0x31, {"AND",&Px6502CPU::AND,&Px6502CPU::INDY,5,true}},
            // Arithmetic Shift Left
            {0x0A, {"ASL",&Px6502CPU::ASL,&Px6502CPU::ACC,2,false}},
            {0x06, {"ASL",&Px6502CPU::ASL,&Px6502CPU::ZP0,5,false}},
            {0x16, {"ASL",&Px6502CPU::ASL,&Px6502CPU::ZPX,6,false}},
            {0x0E, {"ASL",&Px6502CPU::ASL,&Px6502CPU::ABS,6,false}},
            {0x1E, {"ASL",&Px6502CPU::ASL,&Px6502CPU::ABSX,7,false}},
            // Branch If Carry Clear
            {0x90, {"BCC",&Px6502CPU::BCC,&Px6502CPU::REL,2,true}},
            // Branch If Carry Set
            {0xB0, {"BCS",&Px6502CPU::BCS,&Px6502CPU::REL,2,true}},
            // Branch If Equal
            {0xF0, {"BEQ",&Px6502CPU::BEQ,&Px6502CPU::REL,2,true}},
            // BIT Test
            {0x24, {"BIT",&Px6502CPU::BIT,&Px6502CPU::ZP0,3,false}},
            {0x2C, {"BIT",&Px6502CPU::BIT,&Px6502CPU::ABS,4,false}},
            // Branch If Minus
            {0x30, {"BMI",&Px6502CPU::BMI,&Px6502CPU::REL,2,true}},
            // Branch If Not Equal
            {0xD0, {"BNE",&Px6502CPU::BNE,&Px6502CPU::REL,2,true}},
            // Branch If Positive
            {0x10, {"BPL",&Px6502CPU::BPL,&Px6502CPU::REL,2,true}},
            // Break - Force Interrupt
            {0x00, {"BRK",&Px6502CPU::BRK,&Px6502CPU::IMP,7,false}},
            // Branch If Overflow Clear
            {0x50, {"BVC",&Px6502CPU::BVC,&Px6502CPU::REL,2,true}},
            // Branch If Overflow Set
            {0x70, {"BVS",&Px6502CPU::BVS,&Px6502CPU::REL,2,true}},
            // Clear Carry Flag
            {0x18, {"CLC",&Px6502CPU::CLC,&Px6502CPU::IMP,2,false}},
            // Clear Decimal Mode
            {0xD8, {"CLD",&Px6502CPU::CLD,&Px6502CPU::IMP,2,false}},
            // Clear Interrup Disable
            {0x58, {"CLI",&Px6502CPU::CLI,&Px6502CPU::IMP,2,false}},
            // Clear Overflow Flag
            {0xB8, {"CLV",&Px6502CPU::CLV,&Px6502CPU::IMP,2,false}},
            // Compare
            {0xC9, {"CMP",&Px6502CPU::CMP,&Px6502CPU::IMM,2,false}},
            {0xC5, {"CMP",&Px6502CPU::CMP,&Px6502CPU::ZP0,3,false}},
            {0xD5, {"CMP",&Px6502CPU::CMP,&Px6502CPU::ZPX,4,false}},
            {0xCD, {"CMP",&Px6502CPU::CMP,&Px6502CPU::ABS,4,false}},
            {0xDD, {"CMP",&Px6502CPU::CMP,&Px6502CPU::ABSX,4,true}},
            {0xD9, {"CMP",&Px6502CPU::CMP,&Px6502CPU::ABSY,4,true}},
            {0xC1, {"CMP",&Px6502CPU::CMP,&Px6502CPU::INDX,6,false}},
            {0xD1, {"CMP",&Px6502CPU::CMP,&Px6502CPU::INDY,5,true}},
            // Compare X Register
            {0xE0, {"CPX",&Px6502CPU::CPX,&Px6502CPU::IMM,2,false}},
            {0xE4, {"CPX",&Px6502CPU::CPX,&Px6502CPU::ZP0,3,false}},
            {0xEC, {"CPX",&Px6502CPU::CPX,&Px6502CPU::ABS,4,false}},
            // Compare Y Register
            {0xC0, {"CPY",&Px6502CPU::CPY,&Px6502CPU::IMM,2,false}},
            {0xC4, {"CPY",&Px6502CPU::CPY,&Px6502CPU::ZP0,3,false}},
            {0xCC, {"CPY",&Px6502CPU::CPY,&Px6502CPU::ABS,4,false}},
            // Decrement Memory
            {0xC6, {"DEC",&Px6502CPU::DEC,&Px6502CPU::ZP0,5,false}},
            {0xD6, {"DEC",&Px6502CPU::DEC,&Px6502CPU::ZPX,6,false}},
            {0xCE, {"DEC",&Px6502CPU::DEC,&Px6502CPU::ABS,6,false}},
            {0xDE, {"DEC",&Px6502CPU::DEC,&Px6502CPU::ABSX,7,false}},
            // Decrement X Register
            {0xCA, {"DEX",&Px6502CPU::DEX,&Px6502CPU::IMP,2,false}},
            // Decrement Y Register
            {0x88, {"DEY",&Px6502CPU::DEY,&Px6502CPU::IMP,2,false}},
            // Exclusive OR
            {0x49, {"EOR",&Px6502CPU::EOR,&Px6502CPU::IMM,2,false}},
            {0x45, {"EOR",&Px6502CPU::EOR,&Px6502CPU::ZP0,3,false}},
            {0x55, {"EOR",&Px6502CPU::EOR,&Px6502CPU::ZPX,4,false}},
            {0x4D, {"EOR",&Px6502CPU::EOR,&Px6502CPU::ABS,4,false}},
            {0x5D, {"EOR",&Px6502CPU::EOR,&Px6502CPU::ABSX,4,true}},
            {0x59, {"EOR",&Px6502CPU::EOR,&Px6502CPU::ABSY,4,true}},
            {0x41, {"EOR",&Px6502CPU::EOR,&Px6502CPU::INDX,6,false}},
            {0x51, {"EOR",&Px6502CPU::EOR,&Px6502CPU::INDY,5,true}},
            // Increment Memory
            {0xE6, {"INC",&Px6502CPU::INC,&Px6502CPU::ZP0,5,false}},
            {0xF6, {"INC",&Px6502CPU::INC,&Px6502CPU::ZPX,6,false}},
            {0xEE, {"INC",&Px6502CPU::INC,&Px6502CPU::ABS,6,false}},
            {0xFE, {"INC",&Px6502CPU::INC,&Px6502CPU::ABSX,7,false}},
            // Increment X Register
            {0xE8, {"INX",&Px6502CPU::INX,&Px6502CPU::IMP,2,false}},
            // Increment Y Register
            {0xC8, {"INY",&Px6502CPU::INY,&Px6502CPU::IMP,2,false}},
            // Jump
            {0x4C, {"JMP",&Px6502CPU::JMP,&Px6502CPU::ABS,3,false}},
            {0x6C, {"JMP",&Px6502CPU::JMP,&Px6502CPU::IND,5,false}},
            // Jump Subroutine
            {0x20, {"JSR",&Px6502CPU::JSR,&Px6502CPU::ABS,6,false}},
            // Load Accumulator
            {0xA9, {"LDA",&Px6502CPU::LDA,&Px6502CPU::IMM,2,false}},
            {0xA5, {"LDA",&Px6502CPU::LDA,&Px6502CPU::ZP0,3,false}},
            {0xB5, {"LDA",&Px6502CPU::LDA,&Px6502CPU::ZPX,4,false}},
            {0xAD, {"LDA",&Px6502CPU::LDA,&Px6502CPU::ABS,4,false}},
            {0xBD, {"LDA",&Px6502CPU::LDA,&Px6502CPU::ABSX,4,true}},
            {0xB9, {"LDA",&Px6502CPU::LDA,&Px6502CPU::ABSY,4,true}},
            {0xA1, {"LDA",&Px6502CPU::LDA,&Px6502CPU::INDX,6,false}},
            {0xB1, {"LDA",&Px6502CPU::LDA,&Px6502CPU::INDY,5,true}},
            // Load X Register
            {0xA2, {"LDX",&Px6502CPU::LDX,&Px6502CPU::IMM,2,false}},
            {0xA6, {"LDX",&Px6502CPU::LDX,&Px6502CPU::ZP0,3,false}},
            {0xB6, {"LDX",&Px6502CPU::LDX,&Px6502CPU::ZPY,4,false}},
            {0xAE, {"LDX",&Px6502CPU::LDX,&Px6502CPU::ABS,4,false}},
            {0xBE, {"LDX",&Px6502CPU::LDX,&Px6502CPU::ABSY,4,true}},
            // Load Y Register
            {0xA0, {"LDY",&Px6502CPU::LDY,&Px6502CPU::IMM,2,false}},
            {0xA4, {"LDY",&Px6502CPU::LDY,&Px6502CPU::ZP0,3,false}},
            {0xB4, {"LDY",&Px6502CPU::LDY,&Px6502CPU::ZPX,4,false}},
            {0xAC, {"LDY",&Px6502CPU::LDY,&Px6502CPU::ABS,4,false}},
            {0xBC, {"LDY",&Px6502CPU::LDY,&Px6502CPU::ABSX,4,true}},
            // Logical Shift Right
            {0x4A, {"LSR",&Px6502CPU::LSR,&Px6502CPU::ACC,2,false}},
            {0x46, {"LSR",&Px6502CPU::LSR,&Px6502CPU::ZP0,5,false}},
            {0x56, {"LSR",&Px6502CPU::LSR,&Px6502CPU::ZPX,6,false}},
            {0x4E, {"LSR",&Px6502CPU::LSR,&Px6502CPU::ABS,6,false}},
            {0x5E, {"LSR",&Px6502CPU::LSR,&Px6502CPU::ABSX,7,false}},
            // No Operation
            {0xEA, {"NOP",&Px6502CPU::NOP,&Px6502CPU::IMP,2,false}},
            // Logical Inclusive OR
            {0x09, {"ORA",&Px6502CPU::ORA,&Px6502CPU::IMM,2,false}},
            {0x05, {"ORA",&Px6502CPU::ORA,&Px6502CPU::ZP0,3,false}},
            {0x15, {"ORA",&Px6502CPU::ORA,&Px6502CPU::ZPX,4,false}},
            {0x0D, {"ORA",&Px6502CPU::ORA,&Px6502CPU::ABS,4,false}},
            {0x1D, {"ORA",&Px6502CPU::ORA,&Px6502CPU::ABSX,4,true}},
            {0x19, {"ORA",&Px6502CPU::ORA,&Px6502CPU::ABSY,4,true}},
            {0x01, {"ORA",&Px6502CPU::ORA,&Px6502CPU::INDX,6,false}},
            {0x11, {"ORA",&Px6502CPU::ORA,&Px6502CPU::INDY,5,true}},
            // Push Accumulator
            {0x48, {"PHA",&Px6502CPU::PHA,&Px6502CPU::IMP,3,false}},
            // Push Processor Status
            {0x08, {"PHP",&Px6502CPU::PHP,&Px6502CPU::IMP,3,false}},
            // Pull Accumulator
            {0x68, {"PLA",&Px6502CPU::PLA,&Px6502CPU::IMP,4,false}},
            // Pull Processor Status
            {0x28, {"PLP",&Px6502CPU::PLP,&Px6502CPU::IMP,4,false}},
            // Rotate Left
            {0x2A, {"ROL",&Px6502CPU::ROL,&Px6502CPU::ACC,2,false}},
            {0x26, {"ROL",&Px6502CPU::ROL,&Px6502CPU::ZP0,5,false}},
            {0x36, {"ROL",&Px6502CPU::ROL,&Px6502CPU::ZPX,6,false}},
            {0x2E, {"ROL",&Px6502CPU::ROL,&Px6502CPU::ABS,6,false}},
            {0x3E, {"ROL",&Px6502CPU::ROL,&Px6502CPU::ABSX,7,false}},
            // Rotate Right
            {0x6A, {"ROR",&Px6502CPU::ROR,&Px6502CPU::ACC,2,false}},
            {0x66, {"ROR",&Px6502CPU::ROR,&Px6502CPU::ZP0,5,false}},
            {0x76, {"ROR",&Px6502CPU::ROR,&Px6502CPU::ZPX,6,false}},
            {0x6E, {"ROR",&Px6502CPU::ROR,&Px6502CPU::ABS,6,false}},
            {0x7E, {"ROR",&Px6502CPU::ROR,&Px6502CPU::ABSX,7,false}},
            // Return from Interrupt
            {0x40, {"RTI",&Px6502CPU::RTI,&Px6502CPU::IMP,6,false}},
            // Return from Subroutine
            {0x60, {"RTS",&Px6502CPU::RTS,&Px6502CPU::IMP,6,false}},
            // Substract with Carry
            {0xE9, {"SBC",&Px6502CPU::SBC,&Px6502CPU::IMM,2,false}},
            {0xE5, {"SBC",&Px6502CPU::SBC,&Px6502CPU::ZP0,3,false}},
            {0xF5, {"SBC",&Px6502CPU::SBC,&Px6502CPU::ZPX,4,false}},
            {0xED, {"SBC",&Px6502CPU::SBC,&Px6502CPU::ABS,4,false}},
            {0xFD, {"SBC",&Px6502CPU::SBC,&Px6502CPU::ABSX,4,true}},
            {0xF9, {"SBC",&Px6502CPU::SBC,&Px6502CPU::ABSY,4,true}},
            {0xE1, {"SBC",&Px6502CPU::SBC,&Px6502CPU::INDX,6,false}},
            {0xF1, {"SBC",&Px6502CPU::SBC,&Px6502CPU::INDY,5,true}},
            // Set Carry Flag
            {0x38, {"SEC",&Px6502CPU::SEC,&Px6502CPU::IMP,2,false}},
            // Set Decimal Flag
            {0xF8, {"SED",&Px6502CPU::SED,&Px6502CPU::IMP,2,false}},
            // Set Interrupt Disable
            {0x78, {"SEI",&Px6502CPU::SEI,&Px6502CPU::IMP,2,false}},
            // Store Accumulator
            {0x85, {"STA",&Px6502CPU::STA,&Px6502CPU::ZP0,3,false}},
            {0x95, {"STA",&Px6502CPU::STA,&Px6502CPU::ZPX,4,false}},
            {0x8D, {"STA",&Px6502CPU::STA,&Px6502CPU::ABS,4,false}},
            {0x9D, {"STA",&Px6502CPU::STA,&Px6502CPU::ABSX,5,false}},
            {0x99, {"STA",&Px6502CPU::STA,&Px6502CPU::ABSY,5,false}},
            {0x81, {"STA",&Px6502CPU::STA,&Px6502CPU::INDX,6,false}},
            {0x91, {"STA",&Px6502CPU::STA,&Px6502CPU::INDY,6,false}},
            // Store X Register
            {0x86, {"STX",&Px6502CPU::STX,&Px6502CPU::ZP0,3,false}},
            {0x96, {"STX",&Px6502CPU::STX,&Px6502CPU::ZPY,4,false}},
            {0x8E, {"STX",&Px6502CPU::STX,&Px6502CPU::ABS,4,false}},
            // Store Y Register
            {0x84, {"STY",&Px6502CPU::STY,&Px6502CPU::ZP0,3,false}},
            {0x94, {"STY",&Px6502CPU::STY,&Px6502CPU::ZPX,4,false}},
            {0x8C, {"STY",&Px6502CPU::STY,&Px6502CPU::ABS,4,false}},
            // Transfer Accumulator to Register X
            {0xAA, {"TAX",&Px6502CPU::TAX,&Px6502CPU::IMP,2,false}},
            // Transfer Accumulator to Register Y
            {0xA8, {"TAY",&Px6502CPU::TAY,&Px6502CPU::IMP,2,false}},
            // Transfer Stack Pointer to Register X
            {0xBA, {"TSX",&Px6502CPU::TSX,&Px6502CPU::IMP,2,false}},
            // Transfer X Register to Accumulator
            {0x8A, {"TXA",&Px6502CPU::TXA,&Px6502CPU::IMP,2,false}},
            // Transfer X Register to Stack Pointer
            {0x9A, {"TXS",&Px6502CPU::TXS,&Px6502CPU::IMP,2,false}},
            // Transfer Y Register to Accumulator
            {0x98, {"TYA",&Px6502CPU::TYA,&Px6502CPU::IMP,2,false}},
        };

    // CPU POWER UP STATE
    setFlag(B,true);
    setFlag(U,true);
    a = 0x00;
    x = 0x00;
    y = 0x00;
    // write(0x4017,0x00);
    // write(0x4015,0x00);

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
        if(operationLookup.count(opcode)){
            cycles = operationLookup[opcode].cycles;

            uint8_t additional_cycle_addressing = (this->*operationLookup[opcode].pAddressingFunction)();
            uint8_t additional_cycle_operation = (this->*operationLookup[opcode].pOperationFunction)();
            
            if(operationLookup[opcode].canHaveAdditionalCycles){
                cycles += additional_cycle_addressing + additional_cycle_operation;
            }
        } else {
            std::cout << "Problem occured, OPCODE: " << (int)opcode;
            return;
        }
    }
    total_cycle_count++;
    cycles--;
    setFlag(U,true);

}

void Px6502CPU::clockByInstruction(){
    do{
        clock();
    }
    while(cycles > 0);
}

// Reset the CPU state
// Sets the registers to 0, sets Status Flags 0 except Unused
// Load Program Counter from Vector Pointer $FFFC and $FFFD
void Px6502CPU::reset(){
    // Read the New Program Counter from Vector 
    // read($FFFC) -> PC LSB, read($FFFD) -> PC MSB
    uint8_t LSB = read(0xFFFC);
    uint8_t MSB = read(0xFFFD);

    pc = (MSB << 8) + LSB;

    // Reset the Registers
    a = 0;
    x = 0;
    y = 0;
    sp = 0xFD;
    status = 0;
    setFlag(U,true);

    // Also reset other variables
    relative_address = 0;
    effective_address = 0;
    fethced_data = 0;

    // Reset takes some time
    cycles = 8;
}


// Interrup Request
// Source: http://archive.6502.org/datasheets/synertek_programming_manual.pdf
void Px6502CPU::irq(){
    // Check If interrupts are allowed
    if(getFlag(I) == 0){
        // Push program counter to Stack. MSB first.
        write(0x0100 + sp, pc >> 8);
        sp--;
        write(0x0100 + sp, pc & 0x00FF);
        sp--;

        // Push the Status Register to Stack
        setFlag(B, false);
        setFlag(U,true);
        setFlag(I,true);
        write(0x0100 + sp, status);
        sp--;

        // Read the New Program Counter from Vector 
        // read($FFFE) -> PC LSB, read($FFFF) -> PC MSB
        uint8_t LSB = read(0xFFFE);
        uint8_t MSB = read(0xFFFF);

        pc = (MSB << 8) + LSB;

        cycles = 7;
    }
}

// Non Maskable Interrupt can not be ignored. Behaves same as IRQ but its Vector Pointer is in address $FFFA and $FFFB
void Px6502CPU::nmi(){
    // Push program counter to Stack. MSB first.
    write(0x0100 + sp, pc >> 8);
    sp--;
    write(0x0100 + sp, pc & 0x00FF);
    sp--;
    
    // Push the Status Register to Stack
    setFlag(B, false);
    setFlag(U,true);
    setFlag(I,true);
    write(0x0100 + sp, status);
    sp--;
    
    // Read the New Program Counter from Vector 
    // read($FFFA) -> PC LSB, read($FFFB) -> PC MSB
    uint8_t LSB = read(0xFFFA);
    uint8_t MSB = read(0xFFFB);
    
    pc = (MSB << 8) + LSB;
    
    cycles = 8;

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

    uint16_t operand =  (operand_MSB << 8) + operand_LSB;

    effective_address = ( (read(operand+1) << 8) + read(operand) );
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
uint8_t Px6502CPU::ADC(){
    fethced_data = read(effective_address);

        uint8_t temp = a + fethced_data + getFlag(C);

        bool accumulatorSignBit = a & (0b10000000);                 // Get Bit 7 of the Accumulator
        bool fethedDataSignBit = fethced_data & (0b10000000);       // Get Bit 7 of the Fetched Memory Data
        bool tempDataSignBit = temp & (0b10000000);                 // Get Bit 7 of the Addition

        // Set Overflow Truth Table
        // fethedDataSignBit | accumulatorSignBit | tempDataSignBit |  Overflow Status
        //        0          |          0         |         0       |         0         Positive + Positive = Positive
        //        0          |          0         |         1       |         1         Positive + Positive = Negative !!!! OVERFLOW
        //        0          |          1         |         0       |         0         Positive + Negative = Positive 
        //        0          |          1         |         1       |         0         Positive + Negative = Negative
        //        1          |          0         |         0       |         0         Negative + Positive = Positive
        //        1          |          0         |         1       |         0         Negative + Positive = Negative
        //        1          |          1         |         0       |         1         Negative + Negative = Positive !!!! OVERFLOW
        //        1          |          1         |         1       |         0         Negative + Negative = Negative
        setFlag(V, (fethedDataSignBit == accumulatorSignBit) and (tempDataSignBit != accumulatorSignBit) );
        setFlag(C, temp < (a + fethced_data));                      // Set the Carry Flag if result is smaller than addition
        setFlag(N, (temp & 0b10000000) > 0);                        // Set Negative Flag if Sign Bit is set
        setFlag(Z, temp == 0x00);                                   // Set Zero Flag if result is 0
        
        // Set result to Accumulator
        a = temp;

        return 0;

}

uint8_t Px6502CPU::AND(){
    a = a & read(effective_address);
    setFlag(Z, a == 0x00);                                          // Set Zero Flag if result is 0       
    setFlag(N,(a & 0b10000000) > 0);                                // Set Negative Flag if Sign Bit is set
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
    setFlag(Z, temp == 0x00);                                  // Set Zero Flag if result is 0
    setFlag(N, (temp & 0b10000000) > 0);                       // Set Negative Flag if Sign Bit is set

    if(operationLookup[opcode].pAddressingFunction == &Px6502CPU::ACC)
        a = temp;
    else
        write(effective_address,temp);

    return 0;
}
// BRANCHING INSTRUCTIONS:
// Relative address is 8 bit signed integer.
// Set the new program counter to relative address.
// Return additional clock cycles:
//       1 more if successful 2 more if successful and page changed

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

uint8_t Px6502CPU::BIT(){
    fethced_data = read(effective_address);
    uint8_t temp = a & fethced_data;
    setFlag(Z, temp == 0x00);
    setFlag(N,(fethced_data & 0b10000000) > 0);
    setFlag(V,(fethced_data & 0b01000000) > 0);
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


// FLAG INSTRUCTIONS
// Set or Clear Flag

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
    pc++;
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
    // Get Twos complement on fetched data.
    // Formulae for the Subtraction is -> A = A-M-(1-C) -> A = A - M -1 + C
    // We can change M to its negative with twos complement. -M = + (M^0xFF +1) -> We Use 0xFF bc MOS 6502 is a 8-bit CPU.
    // A -M -1 +C = A + (M^0xFF) + C
    // Formulae turned to addition with flipping the bits in M.
    fethced_data ^= 0xFF;
    // fethced_data += 1;
    uint8_t temp = a + fethced_data + getFlag(C);

    

    bool accumulatorSignBit = a & (0b10000000);                 // Get Bit 7 of the Accumulator
    bool fethedDataSignBit = fethced_data & (0b10000000);       // Get Bit 7 of the Fetched Memory Data
    bool tempDataSignBit = temp & (0b10000000);                 // Get Bit 7 of the Addition.

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
    setFlag(V, (fethedDataSignBit == accumulatorSignBit) and (tempDataSignBit != accumulatorSignBit));

    setFlag(C, temp < (a + fethced_data));
    std::cout << (int)(a) << " + " << (int) fethced_data << " = " << (int) ((int8_t)temp) << std::endl;
    a = temp;

    setFlag(N, (a & 0b10000000) > 0);
    setFlag(Z, a == 0x00);

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
