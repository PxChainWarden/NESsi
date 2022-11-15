#include <cstdint>
#include <array>
#include "Px6502CPU.h"

class Bus
{
private:
    std::array<uint8_t, 64*1024> memory;   
public:
    Px6502CPU cpu; 
    Bus(/* args */);
    ~Bus();
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t data);
};

