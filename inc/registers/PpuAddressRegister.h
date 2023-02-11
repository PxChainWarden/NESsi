#include "Register.h"

class PpuAddressRegister : public Register_16Bit
{
private:
    
public:
    enum ADDRESS_FLAGS{
        T0 = 0,
        T1 = 1,
        T2 = 2,
        P = 3,
        C0 = 4,
        C1 = 5,
        C2 = 6,
        C3 = 7,
        R0 = 8,
        R1 = 9,
        R2 = 10,
        R3 = 11,
        H = 12
    };
    
    
    PpuAddressRegister(/* args */);
    ~PpuAddressRegister();

    uint8_t getFineYOffset();
    uint8_t getBitPlane();
    uint8_t getTileRow();
    uint8_t getTileColumn();
    uint8_t getPatternTableIndex();

    void setFineYOffset(uint8_t data);
    void setBitPlane(uint8_t data);
    void setTileRow(uint8_t data);
    void setTileColumn(uint8_t data);
    void setPatternTableIndex(uint8_t data);
};
