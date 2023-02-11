#include "Bus.h"

Bus::Bus(/* args */)
{
    this->cpu.connectBus(this);

    for(auto &i : this->memory)
        i = 0x00;
}

Bus::~Bus()
{
}

// Map the NES addresses. NES has 2KB of RAM.
// But has 8KB address range to access ram. Other 6KB is mirror of whats in the first 2KB.
// NES access PPU registers by $2000-$2007 addresses. $2008-$3FFF	Mirrors of $2000-2007 (repeats every 8 bytes)
// Source: https://www.nesdev.org/wiki/CPU_memory_map
uint8_t Bus::read(uint16_t address){
    if(address >= 0x0000 && address <= 0x1FFF){
        return this->memory[address & 0x07FF];              // Mod With 2048, Get Data from first 2KB
    } else if(address >= 0x2000 && address <= 0x3FFF){
        return this->ppu.cpuReadFromPPU(address);           // Read From PPU
    } else if(address >= 0x4000 && address <= 0x4017){      // TODO: APU and I/O Registers 
        return 0x00;
    } else if(address >= 0x4018 && address <= 0x401F){      // TODO: APU and I/O functionality that is normally disabled.

    } else if(address >= 0x4020 && address <= 0xFFFF){
        return this->cartridge->cpuReadFromCartridge(address);
    }
        
    return 0x00;
}

void Bus::write(uint16_t address, uint8_t data){
    if(address >= 0x0000 && address <= 0x1FFF){
        this->memory[address & 0x07FF] = data;              // Mod With 2048, Get Data from first 2KB
    } else if(address >= 0x2000 && address <= 0x3FFF){
        this->ppu.cpuWriteToPPU(address, data);             // Read From PPU
    } else if(address >= 0x4000 && address <= 0x4017){      // TODO: APU and I/O Registers 
        return;
    } else if(address >= 0x4018 && address <= 0x401F){      // TODO: APU and I/O functionality that is normally disabled.
        return;
    } else if(address >= 0x4020 && address <= 0xFFFF){
        return;
        //this->cartridge.readFromCartridge(address);
    }
}

void Bus::attachCartridge(std::shared_ptr<PxCartridge>& cartridge){
    this->cartridge = cartridge;
    this->ppu.connectCartridge(cartridge);
}
