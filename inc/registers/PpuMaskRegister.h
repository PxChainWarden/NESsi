#include "Register.h"

class PpuMaskRegister : public Register_8Bit
{
private:
    
public:
    // Mask ($2001) > write
    //
    // Common name: PPUMASK
    // Description: PPU mask register
    // Access: write
    //
    // This register controls the rendering of sprites and backgrounds, as well as colour effects. 
    // 7  bit  0
    // ---- ----
    // BGRs bMmG
    // |||| ||||
    // |||| |||+- Greyscale (0: normal color, 1: produce a greyscale display)
    // |||| ||+-- 1: Show background in leftmost 8 pixels of screen, 0: Hide
    // |||| |+--- 1: Show sprites in leftmost 8 pixels of screen, 0: Hide
    // |||| +---- 1: Show background
    // |||+------ 1: Show sprites
    // ||+------- Emphasize red (green on PAL/Dendy)
    // |+-------- Emphasize green (red on PAL/Dendy)
    // +--------- Emphasize blue

    enum MASK_FLAGS{
        g = 0,
        m = 1,
        M = 2,
        b = 3,
        s = 4,
        R = 5,
        G = 6,
        B = 7
    };
    
    
    PpuMaskRegister(/* args */);
    ~PpuMaskRegister();

    uint8_t getGrayscale();
    uint8_t getShowBackgroundLeftmost();
    uint8_t getShowSpriteLeftmost();
    uint8_t getShowBackground();
    uint8_t getShowSprite();
    uint8_t getEmphasizeRed();
    uint8_t getEmphasizeGreen();
    uint8_t getEmphasizeBlue();

    PpuMaskRegister& operator=(uint8_t reg);

    void setGrayscale(uint8_t data);
    void setShowBackgroundLeftmost(uint8_t data);
    void setShowSpriteLeftmost(uint8_t data);
    void setShowBackground(uint8_t data);
    void setShowSprite(uint8_t data);
    void setEmphasizeRed(uint8_t data);
    void setEmphasizeGreen(uint8_t data);
    void setEmphasizeBlue(uint8_t data);
};
