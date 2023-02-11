#pragma once
#include <cstdint>

#pragma once
#include "PxCartridge.h"

#pragma once
#include <array>


#pragma once
#include <map>

#pragma once
#include <QVariantList>

#pragma once
#include <QVariantMap>

#pragma once
#include "PpuAddressRegister.h"

#pragma once
#include "PpuControlRegister.h"

#pragma once
#include "PpuMaskRegister.h"

class Bus;

class Px2C02PPU
{
private:
    int scanline;

    PpuControlRegister ppu_ctrl;
    PpuMaskRegister ppu_mask;

    union {
        struct{
            uint8_t ppuOpenBus : 5;
            uint8_t spriteOverFlow : 1;
            uint8_t spriteZeroHit: 1;
            uint8_t verticalBlankStarted : 1;
        };

        uint8_t reg;
    } ppu_status;

    PpuAddressRegister ppu_addr;

    bool isAddressLowWrote = false;

//    uint8_t ppu_ctrl = 0x00;        // $2000
//    uint8_t ppu_mask = 0x00;        // $2001
//    uint8_t ppu_status = 0x00;      // $2002
    uint8_t oam_addr = 0x00;        // $2003
    uint8_t oam_data = 0x00;        // $2004
    uint8_t ppu_scroll = 0x00;      // $2005
//    uint16_t ppu_addr = 0x00;        // $2006
    uint8_t ppu_data = 0x00;        // $2007
    uint8_t oam_dma = 0x00;         // $4014

    const int SCANLINE_PER_FRAME = 260;
    const int CYCLE_PER_SCANLINE = 340;

    int scanline = 0;
    int cycle = 0;

//    uint8_t ppu_data_buffer = 0x00;

    Bus * cpuBus = nullptr;
    std::shared_ptr<PxCartridge> cartridge = nullptr;

    struct PixelData{
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    std::array<uint8_t,2 * 1024> vRam;
    std::array< uint8_t, 0x20> paletteRam;
    std::array< QVariantMap, 0x40> palette;

    // PpuAddressRegister ppu_internal_address;
public:
    // std::vector<std::map<std::string,uint8_t>> frameBuffer;
    QVariantList frameBuffer;
    QVariantList patternBuffer[2];
    

public:
    Px2C02PPU(/* args */);
    ~Px2C02PPU();
    void connectCPUBus(Bus* bus);
    void connectCartridge(std::shared_ptr<PxCartridge>& cartridge);
    uint8_t cpuReadFromPPU(uint16_t address);
    void cpuWriteToPPU(uint16_t address, uint8_t data);

//    uint8_t getPatternTable(uint8_t palette);

    void clock();
    void frame();

    uint8_t ppuRead(uint16_t address);
    void ppuWrite(uint16_t address, uint8_t data);

    uint16_t getBaseNameTableAddress();
    QVariantMap getColorFromPaletteRam(uint8_t palette, uint8_t pixel);
    QVariantList getPatternTable(uint8_t patternTableIndex, uint8_t palette);
};
