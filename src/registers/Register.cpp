#include "Register.h"
#pragma once
#include <iostream>

Register_8Bit::Register_8Bit(){
    bit0 = false;
    bit1 = false;
    bit2 = false;
    bit3 = false;
    bit4 = false;
    bit5 = false;
    bit6 = false;
    bit7 = false;
}

Register_8Bit::~Register_8Bit(){
}

bool& Register_8Bit::operator[] (int index){
    bool bit = false;
    switch (index){
        case 0:
            bit = bit0;
            break;
        case 1:
            bit = bit1;
            break;
        case 2:
            bit = bit2;
            break;
        case 3:
            bit = bit3;
            break;
        case 4:
            bit = bit4;
            break;
        case 5:
            bit = bit5;
            break;
        case 6:
            bit = bit6;
            break;
        case 7:
            bit = bit7;
            break;
        default:
            break;
    }
    return bit;
}

Register_8Bit& Register_8Bit::operator= (const uint8_t& reg){
    bit0 = reg & 0x01 > 0;
    bit1 = reg & 0x02 > 0;
    bit2 = reg & 0x04 > 0;
    bit3 = reg & 0x08 > 0;
    bit4 = reg & 0x10 > 0;
    bit5 = reg & 0x20 > 0;
    bit6 = reg & 0x40 > 0;
    bit7 = reg & 0x80 > 0;
    return *this;
}

uint8_t Register_8Bit::to_uint8(){
    uint8_t reg = bit7 << 7 + 
                  bit6 << 6 + 
                  bit5 << 5 + 
                  bit4 << 4 + 
                  bit3 << 3 + 
                  bit2 << 2 + 
                  bit1 << 1 + 
                  bit0 << 0;
    return reg;
}

uint8_t Register_8Bit::getSpecifictBits(unsigned int start, unsigned int end) {
    uint8_t data_ = this->to_uint8();
    // Check if the requested bits are within the bounds of the register
    if (end >= REGISTER_SIZE || start > end) {
      throw std::out_of_range("Requested bits are outside the bounds of the register");
    }

    // Create a mask with the bits to extract
    unsigned int mask = ((1 << (end - start + 1)) - 1) << start;

    // Extract the specified bits
    unsigned int extractedBits = (data_ & mask) >> start;

    // Return the extracted bits as an integer
    return static_cast<int>(extractedBits);
  }
  
void Register_8Bit::setSpecificBits(unsigned int start, unsigned int end, unsigned int data) {
    uint8_t data_ = this->to_uint8();
    // Check if the requested bits are within the bounds of the register
    if (end >= REGISTER_SIZE || start > end) {
      throw std::out_of_range("Requested bits are outside the bounds of the register");
    }

    // Check if the value fits in the specified number of bits
    if (data >= (1 << (end - start + 1))) {
      throw std::out_of_range("Value is too large to fit in the specified number of bits");
    }

    // Create a mask with the bits to set
    unsigned int mask = ((1 << (end - start + 1)) - 1) << start;

    // Clear the specified bits in the data
    data_ &= ~mask;

    // Set the specified bits in the data
    data_ |= (data << start) & mask;

    this->operator=(data_);
  }

bool Register_8Bit::rotate_left(bool carry_bit){
    bool temp_bit = bit7;
    bit7 = bit6;
    bit6 = bit5;
    bit5 = bit4;
    bit4 = bit3;
    bit3 = bit2;
    bit2 = bit1;
    bit1 = bit0;
    bit0 = carry_bit;
    return temp_bit;
}

bool Register_8Bit::rotate_right(bool carry_bit){
    bool temp_bit = bit0;
    bit0 = bit1;
    bit1 = bit2;
    bit2 = bit3;
    bit3 = bit4;
    bit4 = bit5;
    bit5 = bit6;
    bit6 = bit7;
    bit7 = carry_bit;
    return temp_bit;
}

bool Register_8Bit::shift_left(){
    bool temp_bit = bit7;
    bit7 = bit6;
    bit6 = bit5;
    bit5 = bit4;
    bit4 = bit3;
    bit3 = bit2;
    bit2 = bit1;
    bit1 = bit0;
    bit0 = 0;
    return temp_bit;
}

bool Register_8Bit::shift_right(){
    bool temp_bit = bit0;
    bit0 = bit1;
    bit1 = bit2;
    bit2 = bit3;
    bit3 = bit4;
    bit4 = bit5;
    bit5 = bit6;
    bit6 = bit7;
    bit7 = 0;
    return temp_bit;
}


Register_16Bit::Register_16Bit(){
    LSB = 0;
    MSB = 0;
}

Register_16Bit::~Register_16Bit(){
}

bool& Register_16Bit::operator[] (int index) {
    bool bit = false;
    switch(index){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            bit = LSB[index];
            break;
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            bit = MSB[index % 8];
            break;
        default:
            break;
    }
    return bit;
}

void Register_16Bit::operator= (uint16_t reg){
    LSB = reg & 0x00FF;
    MSB = reg >> 8;
}

uint16_t Register_16Bit::to_uint16(){
    uint16_t reg = MSB.to_uint8() << 8 + LSB.to_uint8();
    return reg;
}
