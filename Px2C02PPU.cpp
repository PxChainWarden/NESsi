#include "Px2C02PPU.h"

Px2C02PPU::Px2C02PPU(/* args */)
{
}

Px2C02PPU::~Px2C02PPU()
{
}

// Connect PPU to main bus
void Px2C02PPU::connectCPUBus(Bus* bus){
        this->cpuBus = bus;
}

// Connect Cartridge to PPU
void Px2C02PPU::connectCartridge(PxCartridge* cartridge){
        this->cartridge = cartridge;
}

// TODO: Update read and write functions
// Read from PPU Registers 
// Source: https://www.nesdev.org/wiki/PPU_registers
uint8_t Px2C02PPU::cpuReadFromPPU(uint16_t address){
    uint8_t non_mirrored_address = address % 8;
    switch (non_mirrored_address)
    {
    case 0: // Address $2000, $2008 ...
        return ppu_ctrl;
        break;
    case 1: // Address $2001, $2009 ...
        return ppu_mask;
    case 2: // Address $2002, $200A ...
        return ppu_status;
    case 3: // Address $2003, $200B ...
        return oam_addr;
    case 4: // Address $2004, $200C ...
        return oam_data;
    case 5: // Address $2005, $200D ...
        return ppu_scroll;
    case 6: // Address $2006, $200E ...
        return ppu_addr;
    case 7: // Address $2007, $200F ...
        return ppu_data;
    default:
        break;
    }
    
    return 0x00;
}

// Write to PPU Registers
// Source: https://www.nesdev.org/wiki/PPU_registers
void Px2C02PPU::cpuWriteToPPU(uint16_t address, uint8_t data){
    uint8_t non_mirrored_address = address % 8;
    switch (non_mirrored_address)
    {
    case 0: // Address $2000, $2008 ...
        ppu_ctrl = data;
        break;
    case 1: // Address $2001, $2009 ...
        ppu_mask = data;
        break;
    case 2: // Address $2002, $200A ...
        ppu_status = data;
        break;
    case 3: // Address $2003, $200B ...
        oam_addr = data;
        break;
    case 4: // Address $2004, $200C ...
        oam_data = data;
        break;
    case 5: // Address $2005, $200D ...
        ppu_scroll = data;
        break;
    case 6: // Address $2006, $200E ...
        ppu_addr = data;
        break;
    case 7: // Address $2007, $200F ...
        ppu_data = data;
        break;
    default:
        break;
    }
}