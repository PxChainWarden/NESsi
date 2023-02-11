#include "PpuMaskRegister.h"

PpuMaskRegister::PpuMaskRegister(/* args */)
{
}

PpuMaskRegister::~PpuMaskRegister()
{
}

uint8_t PpuMaskRegister::getGrayscale(){
    return (*this)[g];
}

uint8_t PpuMaskRegister::getShowBackgroundLeftmost(){
    return (*this)[m];
}

uint8_t PpuMaskRegister::getShowSpriteLeftmost(){
    return (*this)[M];
}

uint8_t PpuMaskRegister::getShowBackground(){
    return (*this)[b];
}

uint8_t PpuMaskRegister::getShowSprite(){
    return (*this)[s];
}

uint8_t PpuMaskRegister::getEmphasizeRed(){
    return (*this)[R];
}

uint8_t PpuMaskRegister::getEmphasizeGreen(){
    return (*this)[G];
}

uint8_t PpuMaskRegister::getEmphasizeBlue(){
    return (*this)[B];
}

PpuMaskRegister& PpuMaskRegister::operator=(uint8_t reg){
    Register_8Bit::operator=(reg);
    return *this;
}


void PpuMaskRegister::setGrayscale(uint8_t data){
    (*this)[g] = (data & 0x1) % 2;
}

void PpuMaskRegister::setShowBackgroundLeftmost(uint8_t data){
    (*this)[m] = (data & 0x1) % 2;
}

void PpuMaskRegister::setShowSpriteLeftmost(uint8_t data){
    (*this)[M] = (data & 0x1) % 2;
}

void PpuMaskRegister::setShowBackground(uint8_t data){
    (*this)[b] = (data & 0x1) % 2;
}

void PpuMaskRegister::setShowSprite(uint8_t data){
    (*this)[s] = (data & 0x1) % 2;
}

void PpuMaskRegister::setEmphasizeRed(uint8_t data){
    (*this)[R] = (data & 0x1) % 2;
}

void PpuMaskRegister::setEmphasizeGreen(uint8_t data){
    (*this)[G] = (data & 0x1) % 2;
}

void PpuMaskRegister::setEmphasizeBlue(uint8_t data){
    (*this)[B] = (data & 0x1) % 2;
}