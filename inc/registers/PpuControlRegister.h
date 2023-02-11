#include "Register.h"

class PpuControlRegister : public Register_8Bit
{
private:
    
public:
    // Controller ($2000) > write
    //
    // Common name: PPUCTRL
    // Description: PPU control register
    // Access: write
    //
    // Various flags controlling PPU operation 
    // 7  bit  0
    // ---- ----
    // VPHB SINN
    // |||| ||||
    // |||| ||++- Base nametable address
    // |||| ||    (0 = $2000; 1 = $2400; 2 = $2800; 3 = $2C00)
    // |||| |+--- VRAM address increment per CPU read/write of PPUDATA
    // |||| |     (0: add 1, going across; 1: add 32, going down)
    // |||| +---- Sprite pattern table address for 8x8 sprites
    // ||||       (0: $0000; 1: $1000; ignored in 8x16 mode)
    // |||+------ Background pattern table address (0: $0000; 1: $1000)
    // ||+------- Sprite size (0: 8x8 pixels; 1: 8x16 pixels – see PPU OAM#Byte 1)
    // |+-------- PPU master/slave select
    // |          (0: read backdrop from EXT pins; 1: output color on EXT pins)
    // +--------- Generate an NMI at the start of the
    //            vertical blanking interval (0: off; 1: on)

    enum CONTROL_FLAGS{
        NX = 0,
        NY = 1,
        I = 2,
        S = 3,
        B = 4,
        H = 5,
        P = 6,
        V = 7
    };
    
    
    PpuControlRegister(/* args */);
    ~PpuControlRegister();

    uint8_t getBaseNameTable();
    uint8_t getAddressIncrement();
    uint8_t getSpritePatternTable();
    uint8_t getBackgroundPatternTable();
    uint8_t getSpriteSizeMode();
    uint8_t getPpuMasterSlaveFlag();
    uint8_t getNmiFlag();

    PpuControlRegister& operator=(const uint8_t& reg);

    void setBaseNameTable(uint8_t data);
    void setAddressIncrement(uint8_t data);
    void setSpritePatternTable(uint8_t data);
    void setBackgroundPatternTable(uint8_t data);
    void setSpriteSizeMode(uint8_t data);
    void setPpuMasterSlaveFlag(uint8_t data);
    void setNmiFlag(uint8_t data);
};
