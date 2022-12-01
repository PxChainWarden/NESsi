#pragma once
#include <cstdint>

#pragma once
#include "PxCartridge.h"

class Bus;

class Px2C02PPU
{
private:
    uint8_t ppu_ctrl = 0x00;        // $2000
    uint8_t ppu_mask = 0x00;        // $2001
    uint8_t ppu_status = 0x00;      // $2002
    uint8_t oam_addr = 0x00;        // $2003
    uint8_t oam_data = 0x00;        // $2004
    uint8_t ppu_scroll = 0x00;      // $2005
    uint8_t ppu_addr = 0x00;        // $2006
    uint8_t ppu_data = 0x00;        // $2007
    uint8_t oam_dma = 0x00;         // $4014

    Bus * cpuBus = nullptr;
    PxCartridge* cartridge = nullptr;

public:
    Px2C02PPU(/* args */);
    ~Px2C02PPU();
    void connectCPUBus(Bus* bus);
    void connectCartridge(PxCartridge* cartridge);
    uint8_t cpuReadFromPPU(uint16_t address);
    void cpuWriteToPPU(uint16_t address, uint8_t data);
};
