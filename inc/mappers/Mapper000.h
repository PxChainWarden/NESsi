#pragma once
#include "PxMapper.h"

class Mapper000 : public PxMapper
{
private:
    /* data */
public:
    // Mapper000(/* args */);
    Mapper000(uint8_t prg_bank_count, uint8_t chr_bank_count);
    ~Mapper000();

    uint32_t cpuGetMappedAddress(uint16_t address) override;
    uint32_t ppuReadFromCartridge(uint16_t address) override;
};
