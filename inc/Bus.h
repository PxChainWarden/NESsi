#include <array>
#include "Px6502CPU.h"
#include "Px2C02PPU.h"
#include "PxCartridge.h"

class Bus
{
private:
    std::array<uint8_t, 2*1024> memory;   
public:
    Px6502CPU cpu;
    Px2C02PPU ppu;
    std::shared_ptr<PxCartridge> cartridge;

    Bus(/* args */);
    ~Bus();
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t data);
    void attachCartridge(std::shared_ptr<PxCartridge>& cartridge);
};