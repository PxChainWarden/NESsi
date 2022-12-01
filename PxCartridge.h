#include <vector>
#include <string>
#include <fstream>

#pragma once
#include "PxMapper.h"

#include "Mapper000.h"

class PxCartridge
{
private:
    std::vector<uint8_t> prg_rom;
    std::vector<uint8_t> chr_rom;

    uint8_t prg_rom_banks = 0;
    uint8_t chr_rom_banks = 0;
    uint8_t mapperId;

    std::shared_ptr<PxMapper> mapper_pointer;

public:
    PxCartridge(/* args */);
    PxCartridge(std::string& romFileName);
    ~PxCartridge();
    uint8_t cpuReadFromCartridge(uint16_t address);
    uint8_t ppuReadFromCartridge(uint16_t address);
    
    enum MIRRORING{
        HORIZONTAL,
        VERTICAL
    } mirror = HORIZONTAL;

};

