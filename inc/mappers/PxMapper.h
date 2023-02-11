#pragma once
#include <cstdint>

class PxMapper
{
protected:
    uint8_t prg_bank_count = 0;
    uint8_t chr_bank_count = 0;
public:
    PxMapper();
    PxMapper(uint8_t prg_bank_count, uint8_t chr_bank_count);
    ~PxMapper();

    virtual uint32_t cpuGetMappedAddress(uint16_t address) = 0;
    virtual uint32_t ppuReadFromCartridge(uint16_t address) = 0;
};
