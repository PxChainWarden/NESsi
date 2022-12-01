#include "PxCartridge.h"

PxCartridge::PxCartridge(/* args */)
{
}

// Read .nes ROM files
// Source: https://www.nesdev.org/wiki/INES#Name_of_file_format, https://www.nesdev.org/wiki/NROM
PxCartridge::PxCartridge(std::string& romFileName)
{
    struct RomHeader {
        char name[4];
        uint8_t prg_banks;
        uint8_t chr_banks;
        uint8_t mapper1;     // Mapper, mirroring, battery, trainer
        uint8_t mapper2;     // Mapper, VS/Playchoice, NES 2.0
        uint8_t prg_ram_size;
        uint8_t tv_system1;     // TV system (rarely used extension)
        uint8_t tv_system2;     // TV system, PRG-RAM presence (unofficial, rarely used extension)
        char unused[5];
    }RomHeader;

    std::ifstream romFile;
    romFile.open(romFileName, std::ifstream::binary);

    if(romFile.is_open()){
        romFile.read((char*) &RomHeader, sizeof(RomHeader)); // Read the Header

        if(RomHeader.mapper1 & 0b00000100){                  // If trainer is present skip the trainer
            romFile.seekg(512, std::ios::cur);               // Trainer is exactly 512 bytes
        }

        // Mapper ID is HI nibble of both mappers. mapper2 got the Most significant nibble
        mapperId = (RomHeader.mapper1 >> 4) + RomHeader.mapper2 & 0xF0;

        mirror = RomHeader.mapper1 & 0x01 ? VERTICAL : HORIZONTAL;  // Set mirroring mode according to mapper1 bit 0

        prg_rom_banks = RomHeader.prg_banks;
        chr_rom_banks = RomHeader.chr_banks;

        prg_rom.resize(prg_rom_banks * 0x4000);          // bank count * 16KB
        romFile.read( (char*)prg_rom.data(), prg_rom.size());


        chr_rom.resize(chr_rom_banks * 0x2000);         // bank count * 8KB
        romFile.read( (char*)chr_rom.data(), chr_rom.size());

        // Select correct mapper to use
        switch (mapperId)
        {
        case 0:
            mapper_pointer = std::make_shared<Mapper000>(prg_rom_banks,chr_rom_banks);
            break;
        default:
            break;
        }

        romFile.close();


    }
}

PxCartridge::~PxCartridge()
{
}

// Read Cartridge data from CPU
uint8_t PxCartridge::cpuReadFromCartridge(uint16_t address){
    return this->prg_rom[mapper_pointer->cpuGetMappedAddress(address)];
}

// Read Cartridge data from PPU
uint8_t PxCartridge::ppuReadFromCartridge(uint16_t address){
    return 0x00;
}
