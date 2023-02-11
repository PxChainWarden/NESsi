#include "Px2C02PPU.h"

Px2C02PPU::Px2C02PPU(/* args */)
{
    palette[0x00] = {{"r",84},{"b",84},{"g",84},{"a",255}};
    palette[0x01] = {{"r",0},{"g",30},{"b",116},{"a",255}};
    palette[0x02] = {{"r",8},{"g",16},{"b",144},{"a",255}};
    palette[0x03] = {{"r",48},{"g",0},{"b",136},{"a",255}};
    palette[0x04] = {{"r",68},{"g",0},{"b",100},{"a",255}};
    palette[0x05] = {{"r",92},{"g",0},{"b",48},{"a",255}};
    palette[0x06] = {{"r",84},{"g",4},{"b",0},{"a",255}};
    palette[0x07] = {{"r",60},{"g",24},{"b",0},{"a",255}};
    palette[0x08] = {{"r",32},{"g",42},{"b",0},{"a",255}};
    palette[0x09] = {{"r",8},{"g",58},{"b",0},{"a",255}};
    palette[0x0A] = {{"r",0},{"g",64},{"b",0},{"a",255}};
    palette[0x0B] = {{"r",0},{"g",60},{"b",0},{"a",255}};
    palette[0x0C] = {{"r",0},{"g",50},{"b",60},{"a",255}};
    palette[0x0D] = {{"r",0},{"g",0},{"b",0},{"a",255}};
    palette[0x0E] = {{"r",0},{"g",0},{"b",0},{"a",255}};
    palette[0x0F] = {{"r",0},{"g",0},{"b",0},{"a",255}};

    palette[0x10] = {{"r",152},{"g",150},{"b",152},{"a",255}};
    palette[0x11] = {{"r",8},{"g",76},{"b",196},{"a",255}};
    palette[0x12] = {{"r",48},{"g",50},{"b",236},{"a",255}};
    palette[0x13] = {{"r",92},{"g",30},{"b",228},{"a",255}};
    palette[0x14] = {{"r",136},{"g",20},{"b",176},{"a",255}};
    palette[0x15] = {{"r",160},{"g",20},{"b",100},{"a",255}};
    palette[0x16] = {{"r",152},{"g",34},{"b",32},{"a",255}};
    palette[0x17] = {{"r",120},{"g",60},{"b",0},{"a",255}};
    palette[0x18] = {{"r",84},{"g",90},{"b",0},{"a",255}};
    palette[0x19] = {{"r",40},{"g",114},{"b",0},{"a",255}};
    palette[0x1A] = {{"r",8},{"g",124},{"b",0},{"a",255}};
    palette[0x1B] = {{"r",0},{"g",118},{"b",40},{"a",255}};
    palette[0x1C] = {{"r",0},{"g",102},{"b",120},{"a",255}};
    palette[0x1D] = {{"r",0},{"g",0},{"b",0},{"a",255}};
    palette[0x1E] = {{"r",0},{"g",0},{"b",0},{"a",255}};
    palette[0x1F] = {{"r",0},{"g",0},{"b",0},{"a",255}};

    palette[0x20] = {{"r",236},{"g",238},{"b",236},{"a",255}};
    palette[0x21] = {{"r",76},{"g",154},{"b",236},{"a",255}};
    palette[0x22] = {{"r",120},{"g",124},{"b",236},{"a",255}};
    palette[0x23] = {{"r",176},{"g",98},{"b",236},{"a",255}};
    palette[0x24] = {{"r",228},{"g",84},{"b",236},{"a",255}};
    palette[0x25] = {{"r",236},{"g",88},{"b",180},{"a",255}};
    palette[0x26] = {{"r",236},{"g",106},{"b",100},{"a",255}};
    palette[0x27] = {{"r",212},{"g",136},{"b",32},{"a",255}};
    palette[0x28] = {{"r",160},{"g",170},{"b",0},{"a",255}};
    palette[0x29] = {{"r",116},{"g",196},{"b",0},{"a",255}};
    palette[0x2A] = {{"r",76},{"g",208},{"b",32},{"a",255}};
    palette[0x2B] = {{"r",56},{"g",204},{"b",108},{"a",255}};
    palette[0x2C] = {{"r",56},{"g",180},{"b",204},{"a",255}};
    palette[0x2D] = {{"r",60},{"g",60},{"b",60},{"a",255}};
    palette[0x2E] = {{"r",0},{"g",0},{"b",0},{"a",255}};
    palette[0x2F] = {{"r",0},{"g",0},{"b",0},{"a",255}};
    
    palette[0x30] = {{"r",236},{"g",238},{"b",236},{"a",255}};
    palette[0x31] = {{"r",168},{"g",204},{"b",236},{"a",255}};
    palette[0x32] = {{"r",188},{"g",188},{"b",236},{"a",255}};
    palette[0x33] = {{"r",212},{"g",178},{"b",236},{"a",255}};
    palette[0x34] = {{"r",236},{"g",174},{"b",236},{"a",255}};
    palette[0x35] = {{"r",236},{"g",174},{"b",212},{"a",255}};
    palette[0x36] = {{"r",236},{"g",180},{"b",176},{"a",255}};
    palette[0x37] = {{"r",228},{"g",196},{"b",144},{"a",255}};
    palette[0x38] = {{"r",204},{"g",210},{"b",120},{"a",255}};
    palette[0x39] = {{"r",180},{"g",222},{"b",120},{"a",255}};
    palette[0x3A] = {{"r",168},{"g",226},{"b",144},{"a",255}};
    palette[0x3B] = {{"r",152},{"g",226},{"b",180},{"a",255}};
    palette[0x3C] = {{"r",160},{"g",214},{"b",228},{"a",255}};
    palette[0x3D] = {{"r",160},{"g",162},{"b",160},{"a",255}};
    palette[0x3E] = {{"r",0},{"g",0},{"b",0},{"a",255}};
    palette[0x3F] = {{"r",0},{"g",0},{"b",0},{"a",255}};

    frameBuffer.resize(256 * 240);

    patternBuffer[0].resize(128*128);
    patternBuffer[1].resize(128*128);

    paletteRam[0] = 0x0D;
    paletteRam[1] = 0x15;
    paletteRam[2] = 0x3C;
    paletteRam[3] = 0x07;

    paletteRam[4] = 0x0D;
    paletteRam[5] = 0x30;
    paletteRam[6] = 0x27;
    paletteRam[7] = 0x06;

    paletteRam[8] = 0x0D;
    paletteRam[9] = 0x30;
    paletteRam[10] = 0x35;
    paletteRam[11] = 0x07;

    paletteRam[12] = 0x0D;
    paletteRam[13] = 0x30;
    paletteRam[14] = 0x3C;
    paletteRam[15] = 0x24;

    paletteRam[16] = 0x0D;
    paletteRam[17] = 0x02;
    paletteRam[18] = 0x35;
    paletteRam[19] = 0x16;

    paletteRam[20] = 0x0D;
    paletteRam[21] = 0x30;
    paletteRam[22] = 0x17;
    paletteRam[23] = 0x24;

    paletteRam[24] = 0x0D;
    paletteRam[25] = 0x06;
    paletteRam[26] = 0x30;
    paletteRam[27] = 0x37;

    paletteRam[28] = 0x0D;
    paletteRam[29] = 0x01;
    paletteRam[30] = 0x37;
    paletteRam[31] = 0x15;

}

Px2C02PPU::~Px2C02PPU()
{
}

// Connect PPU to main bus
void Px2C02PPU::connectCPUBus(Bus* bus){
        this->cpuBus = bus;
}

// Connect Cartridge to PPU
void Px2C02PPU::connectCartridge(std::shared_ptr<PxCartridge>& cartridge){
        this->cartridge = cartridge;
}

void Px2C02PPU::ppuWrite(uint16_t address, uint8_t data){
    if(address >= 0x0000 && address <= 0x1FFF){
//        cartridge->ppu;
    }else if(address >= 0x2000 && address <= 0x3EFF){
        this->vRam[address % 0x1000] = data;
    }else if(address >= 0x3F00 && address <= 0x3FFF){
        address = address % 0x001F;
        switch (address) {
        case 0x10:
            address = 0x00;
            break;
        case 0x14:
            address = 0x04;
            break;
        case 0x18:
            address = 0x08;
            break;
        case 0x1C:
            address = 0x0C;
            break;
        default:
            break;
        }
        paletteRam[address] = data;
    }

}

uint8_t Px2C02PPU::ppuRead(uint16_t address){
    if(address >= 0x0000 && address <= 0x1FFF){
        return cartridge->ppuReadFromCartridge(address);
    }else if(address >= 0x2000 && address <= 0x3EFF){
        return this->vRam[address % 0x1000];
    }else if(address >= 0x3F00 && address <= 0x3FFF){
        address = address % 0x001F;
        switch (address) {
        case 0x10:
            address = 0x00;
            break;
        case 0x14:
            address = 0x04;
            break;
        case 0x18:
            address = 0x08;
            break;
        case 0x1C:
            address = 0x0C;
            break;
        default:
            break;
        }
        return paletteRam[address];
    }

    return 0x00;
}

// TODO: Update read and write functions
// Read from PPU Registers 
// Source: https://www.nesdev.org/wiki/PPU_registers
uint8_t Px2C02PPU::cpuReadFromPPU(uint16_t address){
    uint8_t non_mirrored_address = address % 8;

    uint8_t data = 0x00;

    switch (non_mirrored_address)
    {
    case 0: // Address $2000, $2008 ...
        // return ppu_ctrl.reg;
        // This is a WRITE ONLY Register
        return 0x00;
        break;
    case 1: // Address $2001, $2009 ...
        data = ppu_mask.to_uint8();
        break;
    case 2: // Address $2002, $200A ...
        data = ppu_status.reg;
        break;
    case 3: // Address $2003, $200B ...
        data = oam_addr;
        break;
    case 4: // Address $2004, $200C ...
        data = oam_data;
        break;
    case 5: // Address $2005, $200D ...
        data = ppu_scroll;
        break;
    case 6: // Address $2006, $200E ...

        break;
    case 7: // Address $2007, $200F ...
        data = ppu_data;
        ppu_data = ppuRead(ppu_addr.to_uint16());

        // NES PPU Normally returns data 1 clock delayed except PPU Palette Data
        if(ppu_addr.to_uint16() >= 0x3F00 && ppu_addr.to_uint16() <= 0x3FFF){
            data = ppu_data;
        }
        break;
    default:
        break;
    }
    
    return data;
}

// Write to PPU Registers
// Source: https://www.nesdev.org/wiki/PPU_registers
void Px2C02PPU::cpuWriteToPPU(uint16_t address, uint8_t data){
    uint8_t non_mirrored_address = address % 8;
    switch (non_mirrored_address)
    {
    case 0: // Address $2000, $2008 ...
        ppu_ctrl = data;
        break;
    case 1: // Address $2001, $2009 ...
        ppu_mask = data;
        break;
    case 2: // Address $2002, $200A ...
        ppu_status.reg = data;
        break;
    case 3: // Address $2003, $200B ...
        oam_addr = data;
        break;
    case 4: // Address $2004, $200C ...
        oam_data = data;
        break;
    case 5: // Address $2005, $200D ...
        ppu_scroll = data;
        break;
    case 6: // Address $2006, $200E ...
        if(!isAddressLowWrote){
            ppu_addr.LSB = data;
            isAddressLowWrote ^= isAddressLowWrote;
        }else{
            ppu_addr.MSB = data;
            isAddressLowWrote ^= isAddressLowWrote;
        }
        break;
    case 7: // Address $2007, $200F ...
        ppu_data = data;
        break;
    default:
        break;
    }
}

// https://www.nesdev.org/wiki/PPU_programmer_reference#Controller_($2000)_%3E_write
uint16_t Px2C02PPU::getBaseNameTableAddress(){
    // Get Last 2 bits of the PPU Control Register
    uint8_t baseNameTable = ppu_ctrl.getBaseNameTable();
    switch (baseNameTable)
    {
    case 0:
        return 0x2000;
    case 1:
        return 0x2400;
    case 2:
        return 0x2800;
    case 3:
        return 0x2C00;
    }
    return 0x00;
}

void Px2C02PPU::clock(){




}

QVariantMap Px2C02PPU::getColorFromPaletteRam(uint8_t palette_index, uint8_t pixel){
    return palette[ppuRead(0x3F00 + (palette_index << 2) + pixel ) & 0x3F];
}

// NES uses 2 pattern tables that are holding 256 tiles (16x16). Each tile in the pattern table is 16 Bytes, made of 2 Planes.
// The First plane controls LSB of 2 bit color
// The Second plane controls MSB of 2 bit color
// $NYXP -> N: Determines the Pattern Table, 0 or 1 aka. left or right pattern table
//          YX: Determines the Tile: 0-255. Y determines the row. X determines the column
//          P:  Determines Bit Plane Data
//
// Example BIT PLANES:
// ADDRESS   |    Data
// PLANE 1
// $NYX0    ->    01000001
// $NYX1    ->    11000010
// $NYX2    ->    01000100
// $NYX3    ->    01001000       PIXEL PATTERN
// $NYX4    ->    00010000
// $NYX5    ->    00100000     ->  .1.....3
// $NYX6    ->    01000000         11....3.
// $NYX7    ->    10000000         .1...3..
// PLANE 2                         .1..3...
// $NYX8    ->    00000001         ...3.22.
// $NYX9    ->    00000010         ..3....2
// $NYXA    ->    00000100         .3....2.
// $NYXB    ->    00001000     ->  3....222
// $NYXC    ->    00010110
// $NYXD    ->    00100001
// $NYXE    ->    01000010
// $NYXF    ->    10000111

// Source: https://www.nesdev.org/wiki/PPU_programmer_reference#Pattern_tables
QVariantList Px2C02PPU::getPatternTable(uint8_t patternTableIndex ,uint8_t palette_index){
    for(uint16_t tile_y = 0; tile_y < 16; tile_y++){
        for(uint16_t tile_x = 0; tile_x < 16; tile_x++){
            //  offset is just the part $NYXP -> YX: tile_y * 256 is = $0Y00, tile_x * 16 = $00X0;
            uint16_t offset = tile_y * 256 + tile_x * 16;

            // Now that we got our tile. We need to create our 8x8 pixel pattern
            for(uint8_t pixel_pattern_y = 0; pixel_pattern_y < 8; pixel_pattern_y++){

                // Getting the pixel pattern row MSB and LSB
                uint8_t pattern_lsb = ppuRead( patternTableIndex * 0x1000 + offset + pixel_pattern_y + 0x0);
                uint8_t pattern_msb = ppuRead( patternTableIndex * 0x1000 + offset + pixel_pattern_y + 0x8);

                for(uint8_t pixel_pattern_x = 0; pixel_pattern_x < 8; pixel_pattern_x++){
                    // Get the most significant bit of the pattern data and create the
                    // pixel data.
                    uint8_t pixel = ( (pattern_msb >> 7) << 1 ) + (pattern_lsb >> 7);

                    // We can shift left by 1 bit. Because the pattern_lsb and pattern_msb
                    // is 8 bit unsigned integer shifting left will not increase the value over 255
                    pattern_lsb <<= 1;
                    pattern_msb <<= 1;

                    // TODO: Improve here.
                    // Set the Pixel Color to the palette Buffer for visualisation of the palette.
                    patternBuffer[patternTableIndex][ (tile_y * 8 + pixel_pattern_y) * 128 + (tile_x * 8 + pixel_pattern_x) ] = getColorFromPaletteRam(palette_index, pixel);;

                }
            }
        }
    }
    return patternBuffer[patternTableIndex];
}

void Px2C02PPU::frame(){
    uint16_t temp_addr = 0x0000;
    for(int scanline = 0; scanline < SCANLINE_PER_FRAME; scanline++){
        for(int pixelCount = 0; pixelCount < PIXEL_PER_SCANLINE; pixelCount++){
            if(scanline < 240 && pixelCount < 256){
            //    qDebug() << scanline * 256 + pixelCount;
                frameBuffer[scanline * 256 + pixelCount] = QVariantMap{{"r",ppuRead(temp_addr % 0x2000)},{"g",ppuRead(temp_addr % 0x2000)},{"b",ppuRead(temp_addr % 0x2000)},{"a",255}};
                temp_addr++;
            }
           clock();
        }
    }
}

void Px2C02PPU::clock(){
    if(scanline == -1){
        // Pre Render Scanline
    }
    if(scanline >= 0 && scanline <= 239){
        // Visible Scanlines
        if(cycle == 0){
            // Idle Cycle
        }
        if(cycle >= 1 && cycle <= 256){
            // Visible Cycles
            switch ( (cycle - 1) % 8 )
            {
            case 0:
            case 1:
                // VRam NameTable Fetch
                break;
            case 2:
            case 3:
                // Vram Attribute Table Fetch
                break;
            case 4:
            case 5:
                // Background LSB Fetch
                break;
            case 6:
                // Background MSB Fetch
                break;
            case 7:
                // Background MSB Fetch
                // Increment X
                break;
            
            default:
                break;
            }
            if(cycle == 256){
                // Increment Y
            }
            
        }
        if(cycle >= 257 && cycle <= 320){
            // The tile data for the sprites on the next scanline are fetched here
        }
        if(cycle >= 321 && cycle <= 336){
            // This is where the first two tiles for the next scanline are fetched, and loaded into the shift registers
        }
        if(cycle >=337 && cycle <= 340){
            // Two bytes are fetched, but the purpose for this is unknown.
        }
    }
    if(scanline == 240){
        // Post-render scanline
    }
    if(scanline >= 241 && scanline <= 260){
        // Vertical blanking lines
        if( scanline == 241 && cycle == 1){
            ppu_status.verticalBlankStarted = 1;
            if(ppu_ctrl.getNmiFlag() == 1){
                // Enable NMI
            }
        }
    }


    // Handle Cycle and Scanline
    cycle++;
    if(cycle > CYCLE_PER_SCANLINE){
        cycle = 0;
        scanline++;
        if(scanline > SCANLINE_PER_FRAME){
            scanline = -1;
        }
    }
}