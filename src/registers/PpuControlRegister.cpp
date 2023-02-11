#include "PpuControlRegister.h"

PpuControlRegister::PpuControlRegister(/* args */)
{
}

PpuControlRegister::~PpuControlRegister()
{
}

uint8_t PpuControlRegister::getBaseNameTable(){
    return ((*this)[NY] << 1) + (*this)[NX];
}

uint8_t PpuControlRegister::getAddressIncrement(){
    return (*this)[I];
}

uint8_t PpuControlRegister::getSpritePatternTable(){
    return (*this)[S];
}

uint8_t PpuControlRegister::getBackgroundPatternTable(){
    return (*this)[B];   
}

uint8_t PpuControlRegister::getSpriteSizeMode(){
    return (*this)[H];
}

uint8_t PpuControlRegister::getPpuMasterSlaveFlag(){
    return (*this)[P];
}

uint8_t PpuControlRegister::getNmiFlag(){
    return (*this)[V];
}

PpuControlRegister& PpuControlRegister::operator=(const uint8_t& reg){
    Register_8Bit::operator=(reg);
    return *this;
}

void PpuControlRegister::setBaseNameTable(uint8_t data){
    (*this)[NX] = (data & 0x1) % 2;
    (*this)[NY] = (data & 0x2) % 2;
}

void PpuControlRegister::setAddressIncrement(uint8_t data){
    (*this)[I] = (data & 0x1) % 2;
}

void PpuControlRegister::setSpritePatternTable(uint8_t data){
    (*this)[S] = (data & 0x1) % 2;
}

void PpuControlRegister::setBackgroundPatternTable(uint8_t data){
    (*this)[B] = (data & 0x1) % 2;
}

void PpuControlRegister::setSpriteSizeMode(uint8_t data){
    (*this)[H] = (data & 0x1) % 2;
}

void PpuControlRegister::setPpuMasterSlaveFlag(uint8_t data){
    (*this)[P] = (data & 0x1) % 2;
}

void PpuControlRegister::setNmiFlag(uint8_t data){
    (*this)[V] = (data & 0x1) % 2;
}
