#include "PpuAddressRegister.h"

PpuAddressRegister::PpuAddressRegister(/* args */)
{
}

PpuAddressRegister::~PpuAddressRegister()
{
}

uint8_t PpuAddressRegister::getFineYOffset(){
    return LSB[T2] << 2 + LSB[T1] << 1 + LSB[T0];
}

uint8_t PpuAddressRegister::getBitPlane(){
    return LSB[P];
}

uint8_t PpuAddressRegister::getTileColumn(){
    return LSB[C3] << 3 + LSB[C2] << 2 + LSB[C1] << 1 + LSB[C0];
}

uint8_t PpuAddressRegister::getTileRow(){
    return MSB[R3 % 8] << 3 + MSB[R2 % 8] << 2 + MSB[R1 % 8] << 1 + MSB[R0 % 8];
}

uint8_t PpuAddressRegister::getPatternTableIndex(){
    return MSB[H % 8];
}

void PpuAddressRegister::setFineYOffset(uint8_t data){
    LSB[T0] = data & 0x1; // Set Bit Zero
    LSB[T1] = data & 0x2; // Set Bit One
    LSB[T2] = data & 0x4; // Set Bit Two
}

void PpuAddressRegister::setBitPlane(uint8_t data){
    LSB[P] = data & 0x1; // Set Bit Zero
}

void PpuAddressRegister::setTileColumn(uint8_t data){
    LSB[C0] = data & 0x1; // Set Bit Zero
    LSB[C1] = data & 0x2; // Set Bit One
    LSB[C2] = data & 0x4; // Set Bit Two
    LSB[C3] = data & 0x8; // Set Bit Three
}

void PpuAddressRegister::setTileRow(uint8_t data){
    MSB[R0 % 8] = data & 0x1; // Set Bit Zero
    MSB[R1 % 8] = data & 0x2; // Set Bit One
    MSB[R2 % 8] = data & 0x4; // Set Bit Two
    MSB[R3 % 8] = data & 0x8; // Set Bit Three
}

void PpuAddressRegister::setPatternTableIndex(uint8_t data){
    MSB[H] = data & 0x1; // Set Bit Zero
}