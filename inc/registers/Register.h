#pragma once
#include <cstdint>

class Register_8Bit
{
private:
    bool bit0 :1;
    bool bit1 :1;
    bool bit2 :1;
    bool bit3 :1;
    bool bit4 :1;
    bool bit5 :1;
    bool bit6 :1;
    bool bit7 :1;

    const unsigned int REGISTER_SIZE = 8;

public:
    Register_8Bit();
    ~Register_8Bit();

    // bool operator[] (int index);
    bool& operator[] (int index);
    Register_8Bit& operator= (const uint8_t& reg);
    uint8_t to_uint8();
    uint8_t getSpecifictBits(unsigned int start, unsigned int end);
    void setSpecificBits(unsigned int start, unsigned int end, unsigned int data);
    bool rotate_left(bool carry_bit);
    bool rotate_right(bool carry_bit);
    bool shift_left();
    bool shift_right();

};

class Register_16Bit
{
private:

public:
    Register_8Bit LSB;
    Register_8Bit MSB;

    Register_16Bit();
    ~Register_16Bit();

    bool& operator[] (int index);
    void operator= (uint16_t reg);
    uint16_t to_uint16();
};
