#include <string>
#include <map>
#include <cstdint>
class Bus;


class Px6502CPU
{
public:
    Bus* bus = nullptr;
    uint8_t a = 0x00;                        // Accumulator
    uint8_t x = 0x00, y =0x00;               // X and Y register
    uint16_t pc = 0x0000;                    // Program Counter
    uint8_t sp = 0x00;                       // Stack Pointer
    uint8_t status = 0x00;                   // Status Register

    uint16_t effective_address = 0x0000;
    uint8_t fethced_data = 0x00;
    uint8_t opcode = 0x00;



    // These are the Status Flags 6502 has. With an enum defined like this changing one specific flag will be easier
    // More on https://www.nesdev.org/wiki/Status_flags
    enum FLAGS{
        C = (1 << 0),                       // Carry Bit
        Z = (1 << 1),                       // Zero Flag
        I = (1 << 2),                       // Interrupt Disable
        D = (1 << 3),                       // Decimal : No Effect On NES
        B = (1 << 4),                       // B-Flag (Break Flag) : Only set if from an instruction (PHP or BRK) or 0 if from an interrupt line being pulled low (/IRQ or /NMI)
        U = (1 << 5),                       // Unused
        V = (1 << 6),                       // Overflow
        N = (1 << 7),                       // Negative
    };

    struct Instruction{
        std::string instruction_name;
        uint8_t (Px6502CPU::*pOperationFunction)(void);
        uint8_t (Px6502CPU::*pAddressingFunction)(void);
        uint8_t cycles;
    };    

private:
    void setFlag(FLAGS flag, bool s);
    uint8_t getFlag(FLAGS flag);

// NES ADDRESSING MODES
// NES uses different methods while accessing data from memory.
// You can look it up more on https://www.nesdev.org/wiki/CPU_addressing_modes and 6502 CPU documents

public:
    uint8_t ACC();                          // Accumulator Access Mode : Many instructions can operate on the accumulator, e.g. LSR A. Some assemblers will treat no operand as an implicit A where applicable.
    uint8_t IMP();                          // Implictic Access Mode : Instructions like RTS or CLC have no address operand, the destination of results are implied.
    uint8_t IMM();                          // Immediate Access Mode : Uses the 8-bit operand itself as the value for the operation, rather than fetching a value from a memory address.
    uint8_t REL();                          // Relative Access Mode : Branch instructions (e.g. BEQ, BCS) have a relative addressing mode that specifies an 8-bit signed offset relative to the current PC.
    uint8_t ZP0();                          // Zero Page Access Mode : Fetches the value from an 8-bit address on the zero page.        
    uint8_t ZPX();                          // Zero Page Indexed Access Mode (X register)
    uint8_t ZPY();                          // Zero Page Indexed Access Mode (Y register)
    uint8_t ABS();                          // Absolute Access Mode : Fetches the value from a 16-bit address anywhere in memory.
    uint8_t ABSX();                         // Absolute Indexed Access Mode (X register)
    uint8_t ABSY();                         // Absolute Indexed Access Mode (Y register)
    uint8_t IND();                          // Indirect Access Mode : The JMP instruction has a special indirect addressing mode that can jump to the address stored in a 16-bit pointer anywhere in memory.
    uint8_t INDX();                         // Indexed Indirect Access Mode (X register)
    uint8_t INDY();                         // Indirect Indexed Access Mode (Y register)


public:
    Px6502CPU(/* args */);
    ~Px6502CPU();

    void clock();

    void connectBus(Bus* bus){
        this->bus = bus;
    }
    
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t data);
    uint8_t fetch();
    std::map<uint8_t,Instruction> operationLookup;


// INSTRUCTIONS
// Details: https://www.nesdev.org/obelisk-6502-guide/reference.html
public:
    uint8_t ADC();      // ADD with Carry
    uint8_t AND();      // Logical AND
    uint8_t ASL();      // Arithmetic Shift Left
    uint8_t BCC();      // Branch if Carry Clear
    uint8_t BCS();      // Branch if Carry Set
    uint8_t BEQ();      // Branch if Equal
    uint8_t BIT();      // Bit Test
    uint8_t BMI();      // Branch if Minus
    uint8_t BNE();      // Branch if Not Equal
    uint8_t BPL();      // Branch if Positive
    uint8_t BRK();      // Force Interrupt
    uint8_t BVC();      // Branch if Overflow Clear
    uint8_t BVS();      // Branch if Overflow Set
    uint8_t CLC();      // Clear Carry Flag
    uint8_t CLD();      // Clear Decimal Mode
    uint8_t CLI();      // Clear Interrupt Disable
    uint8_t CLV();      // Clear Overflow Flag
    uint8_t CMP();      // Compare
    uint8_t CPX();      // Compare X Register
    uint8_t CPY();      // Compare Y Register
    uint8_t DEC();      // Decrement Memory Value
    uint8_t DEX();      // Decrement X Register
    uint8_t DEY();      // Decrement Y Register
    uint8_t EOR();      // Exclusive OR
    uint8_t INC();      // Increment Memory Value
    uint8_t INX();      // Increment X Register
    uint8_t INY();      // Increment Y Register
    uint8_t JMP();      // Jump
    uint8_t JSR();      // Jump Subroutine
    uint8_t LDA();      // Load Accumulator
    uint8_t LDX();      // Load X Register
    uint8_t LDY();      // Load Y Register
    uint8_t LSR();      // Logical Shift Right
    uint8_t NOP();      // No Operation
    uint8_t ORA();      // Logical Inclusive OR
    uint8_t PHA();      // Push Accumulator
    uint8_t PHP();      // Push Processor Status
    uint8_t PLA();      // Pull Accumulator
    uint8_t PLP();      // Pull Processor Status
    uint8_t ROL();      // Rotate Left
    uint8_t ROR();      // Rotate Right
    uint8_t RTI();      // Return from Interrupt
    uint8_t RTS();      // Return from Subroutine
    uint8_t SBC();      // Subtract with Carry
    uint8_t SEC();      // Set Carry Flag
    uint8_t SED();      // Set Decimal Flag
    uint8_t SEI();      // Set Interrupt Disable
    uint8_t STA();      // Store Accumulator
    uint8_t STX();      // Store X Register
    uint8_t STY();      // Store Y Register
    uint8_t TAX();      // Transfer Accumulator to X Register
    uint8_t TAY();      // Transfer Accumulator to Y Register
    uint8_t TSX();      // Transfer Stack Pointer to X Register
    uint8_t TXA();      // Transfer X Register to Accumulator
    uint8_t TXS();      // Transfer X Register to Stack Pointer
    uint8_t TYA();      // Transfer Y Register to Accumulator


};
