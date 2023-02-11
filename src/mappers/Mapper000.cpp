#include "Mapper000.h"

// Mapper000::Mapper000(/* args */)
// {
// }

Mapper000::Mapper000(uint8_t prg_bank_count, uint8_t chr_bank_count) : PxMapper(prg_bank_count, chr_bank_count)
{
}

Mapper000::~Mapper000()
{
}

// Map Reading Address for Mapper 000
// Source https://www.nesdev.org/wiki/NROM
uint32_t Mapper000::cpuGetMappedAddress(uint16_t address){
    if(address >= 0x8000 && address <= 0xFFFF){
        if(prg_bank_count == 1){
            // If bank count is 1 $C000-$FFFF: Last 16 KB of ROM is mirror of $8000-$BFFF.
            // In cartridge our vector starts at 0. so just mod by 16K
            uint32_t mapped_address = (address % 0x4000);
            return mapped_address;
            
        } else{
            // Mod By 32K
            return address % 0x8000;
        }
    }
    return 0x00;
}

// In this type of ROM, there is only 1 bank for chr_data
// chr_data banks are 8KB of memory.
uint32_t Mapper000::ppuReadFromCartridge(uint16_t address){
    // Mod by 8K to get actual vector index
    return address % 0x2000;
}
