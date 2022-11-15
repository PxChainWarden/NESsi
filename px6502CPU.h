#include "Bus.h"

class Px6502CPU
{
private:
    Bus cpuBus;
    uint8_t a = 0x00;                        // Accumulator
    uint8_t x = 0x00, y =0x00;               // X and Y register
    uint16_t pc = 0x0000;                    // Program Counter
    uint8_t sp = 0x00;                       // Stack Pointer
    uint8_t status = 0x00;                   // Status Register

// NES ADDRESSING MODES
// NES uses different methods while accessing data from memory.
// You can look it up more on https://www.nesdev.org/wiki/CPU_addressing_modes and 6502 CPU documents

private:
    uint8_t IMP();                          // Implictic Access Mode : Instructions like RTS or CLC have no address operand, the destination of results are implied.
    uint8_t IMM();                          // Immediate Access Mode : Uses the 8-bit operand itself as the value for the operation, rather than fetching a value from a memory address.
    uint8_t REL();                          // Relative Access Mode : Branch instructions (e.g. BEQ, BCS) have a relative addressing mode that specifies an 8-bit signed offset relative to the current PC.
    uint8_t ZP0();                          // Zero Page Access Mode : Fetches the value from an 8-bit address on the zero page.        
    uint8_t ZPX();                          // Zero Page Indexed Access Mode (X register)
    uint8_t ZPY();                          // Zero Page Indexed Access Mode (Y register)
    uint8_t ABS();                          // Absolute Access Mode : Fetches the value from a 16-bit address anywhere in memory.
    uint8_t ABX();                          // Absolute Indexed Access Mode (X register)
    uint8_t ABY();                          // Absolute Indexed Access Mode (Y register)
    uint8_t IND();                          // Indirect Access Mode : The JMP instruction has a special indirect addressing mode that can jump to the address stored in a 16-bit pointer anywhere in memory.
    uint8_t INX();                          // Indexed Indirect Access Mode (X register)
    uint8_t INY();                          // Indirect Indexed Access Mode (Y register)

public:
    Px6502CPU(/* args */);
    ~Px6502CPU();


    // OPCODE
    uint8_t ADC();
    uint8_t AND();
};
