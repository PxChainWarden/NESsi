#include "testclass.h"
#include <iostream>
#include <fstream>
#include <QRandomGenerator>
#include <QVariant>

TestClass::TestClass(QObject *parent)
    : QObject{parent}
{

//    pixelData test;
//    test.m_a = 255;
//    test.m_b = 84;
//    test.m_g = 84;
//    test.m_r = 84;
    m_palette[0x00] = pixelData(84,84,84,255);
    m_palette[0x01] = pixelData(0,30,116,255);
    m_palette[0x02] = pixelData(8,16,144,255);
    m_palette[0x03] = pixelData(48,0,136,255);
    m_palette[0x04] = pixelData(68,0,100,255);
    m_palette[0x05] = pixelData(92,0,48,255);
    m_palette[0x06] = pixelData(84,4,0,255);
    m_palette[0x07] = pixelData(60,24,0,255);
    m_palette[0x08] = pixelData(32,42,0,255);
    m_palette[0x09] = pixelData(8,58,0,255);
    m_palette[0x0A] = pixelData(0,64,0,255);
    m_palette[0x0B] = pixelData(0,60,0,255);
    m_palette[0x0C] = pixelData(0,50,60,255);
    m_palette[0x0D] = pixelData(0,0,0,255);
    m_palette[0x0E] = pixelData(0,0,0,255);
    m_palette[0x0F] = pixelData(0,0,0,255);

    m_palette[0x10] = pixelData(152,150,152,255);
    m_palette[0x11] = pixelData(8,76,196,255);
    m_palette[0x12] = pixelData(48,50,236,255);
    m_palette[0x13] = pixelData(92,30,228,255);
    m_palette[0x14] = pixelData(136,20,176,255);
    m_palette[0x15] = pixelData(160,20,100,255);
    m_palette[0x16] = pixelData(152,34,32,255);
    m_palette[0x17] = pixelData(120,60,0,255);
    m_palette[0x18] = pixelData(84,90,0,255);
    m_palette[0x19] = pixelData(40,114,0,255);
    m_palette[0x1A] = pixelData(8,124,0,255);
    m_palette[0x1B] = pixelData(0,118,40,255);
    m_palette[0x1C] = pixelData(0,102,120,255);
    m_palette[0x1D] = pixelData(0,0,0,255);
    m_palette[0x1E] = pixelData(0,0,0,255);
    m_palette[0x1F] = pixelData(0,0,0,255);

    m_palette[0x20] = pixelData(236,238,236,255);
    m_palette[0x21] = pixelData(76,154,236,255);
    m_palette[0x22] = pixelData(120,124,236,255);
    m_palette[0x23] = pixelData(176,98,236,255);
    m_palette[0x24] = pixelData(228,84,236,255);
    m_palette[0x25] = pixelData(236,88,180,255);
    m_palette[0x26] = pixelData(236,106,100,255);
    m_palette[0x27] = pixelData(212,136,32,255);
    m_palette[0x28] = pixelData(160,170,0,255);
    m_palette[0x29] = pixelData(116,196,0,255);
    m_palette[0x2A] = pixelData(76,208,32,255);
    m_palette[0x2B] = pixelData(56,204,108,255);
    m_palette[0x2C] = pixelData(56,180,204,255);
    m_palette[0x2D] = pixelData(60,60,60,255);
    m_palette[0x2E] = pixelData(0,0,0,255);
    m_palette[0x2F] = pixelData(0,0,0,255);

    m_palette[0x30] = pixelData(236,238,236,255);
    m_palette[0x31] = pixelData(168,204,236,255);
    m_palette[0x32] = pixelData(188,188,236,255);
    m_palette[0x33] = pixelData(212,178,236,255);
    m_palette[0x34] = pixelData(236,174,236,255);
    m_palette[0x35] = pixelData(236,174,212,255);
    m_palette[0x36] = pixelData(236,180,176,255);
    m_palette[0x37] = pixelData(228,196,144,255);
    m_palette[0x38] = pixelData(204,210,120,255);
    m_palette[0x39] = pixelData(180,222,120,255);
    m_palette[0x3A] = pixelData(168,226,144,255);
    m_palette[0x3B] = pixelData(152,226,180,255);
    m_palette[0x3C] = pixelData(160,214,228,255);
    m_palette[0x3D] = pixelData(160,162,160,255);
    m_palette[0x3E] = pixelData(0,0,0,255);
    m_palette[0x3F] = pixelData(0,0,0,255);
    m_name = "Test";

    m_frame.resize(30*40);
    for(int i = 0; i< 30; i++){
        for(int j = 0; j<40; j++){
            if(j<10){
                m_frame[i*40 + j] = QVariantMap{{"r",m_palette[0x2A].r},{"g",m_palette[0x2A].g},{"b",m_palette[0x2A].b},{"a",m_palette[0x2A].a}};
            }else if (j>30){
                m_frame[i*40 + j] = QVariantMap{{"r",m_palette[0x1C].r},{"g",m_palette[0x1C].g},{"b",m_palette[0x1C].b},{"a",m_palette[0x1C].a}};
            }else {
                m_frame[i*40 + j] = QVariantMap{{"r",m_palette[0x31].r},{"g",m_palette[0x31].g},{"b",m_palette[0x31].b},{"a",m_palette[0x31].a}};
            }
        }
    }



    std::string filename = "/Users/alicank/deneme/nestest.nes";
    std::shared_ptr<PxCartridge> cart = std::make_shared<PxCartridge>(filename);
    bus.attachCartridge(cart);

    bus.ppu.frame();
    bus.ppu.getPatternTable(0,0);
    bus.ppu.getPatternTable(1,0);
//    bus.cpu.pc = 0x4000;
//    std::ifstream infile("/Users/alicank/deneme/AllTestSuiteA.txt", std::fstream::in);

//    unsigned int a;
//    uint16_t starting_address = 0x4000;
//    while(infile >> std::hex >> a){
//        bus.cpu.write(starting_address,a);
//        starting_address++;
//    }


}

QString TestClass::name()
{
    return m_name;
}

QString TestClass::accumulator()
{
    return m_accumulator;
}

QString TestClass::pc()
{
    return m_pc;
}

QString TestClass::sp()
{
    return m_sp;
}

QString TestClass::x()
{
    return m_x;
}

QString TestClass::y()
{
    return m_y;
}

QString TestClass::status()
{
    return m_status;
}

QString TestClass::opcode()
{
    return m_opcode;
}

QString TestClass::clock()
{
    return m_clock;
}

pixelData TestClass::palette()
{
//    index++;
    return m_palette[0];
}

int TestClass::changePalette()
{
    m_palette_index = (m_palette_index + 1) % 8;
    qDebug() << m_palette_index;
    bus.ppu.getPatternTable(0,m_palette_index);
    bus.ppu.getPatternTable(1,m_palette_index);
    emit patternLeftChanged();
    emit patternRightChanged();
    return m_palette_index;
}

QVariantList TestClass::frame()
{
//    index++;
    return bus.ppu.frameBuffer;
}

QVariantList TestClass::pattern(int i)
{
//    index++;
    return bus.ppu.patternBuffer[i];
}

QVariantList TestClass::patternLeft()
{
//    index++;
    return pattern(0);
}

QVariantList TestClass::patternRight()
{
//    index++;
    return pattern(1);
}

void TestClass::setname( QString s)
{
    if( s != m_name){
        m_name = s;
        emit nameChanged();
    }

}

void TestClass::setAccumulator( QString a)
{
    if( a != m_accumulator){
        m_accumulator = a;
        emit accumulatorChanged();
    }

}

void TestClass::setPc( QString pc)
{
    if( pc != m_pc){
        m_pc = pc;
        emit pcChanged();
    }

}

void TestClass::setX( QString x)
{
    if( x != m_x){
        m_x = x;
        emit xChanged();
    }

}

void TestClass::setY( QString y)
{
    if( y != m_y){
        m_y = y;
        emit yChanged();
    }

}

void TestClass::setStatus( QString status)
{
    if( status != m_status){
        m_status = status;
        emit statusChanged();
    }

}

void TestClass::setOpcode( QString opcode)
{
    if( opcode != m_opcode){
        m_opcode = opcode;
        emit opcodeChanged();
    }

}

void TestClass::setSp( QString sp)
{
    if( sp != m_sp){
        m_sp = sp;
        emit spChanged();
    }

}

void TestClass::setClock( QString clock)
{
    if( clock != m_clock){
        m_clock = clock;
        emit clockChanged();
    }

}

void TestClass::setPalette( pixelData a)
{


}

void TestClass::activateClock()
{
//    while(bus.cpu.pc < 0x432D){
//        bus.cpu.clockByInstruction();
//    }
    bus.cpu.clockByInstruction();
    setAccumulator(uintToHex(bus.cpu.a,2));
    setPc(uintToHex(bus.cpu.pc,4));
    setX(uintToHex(bus.cpu.x,2));
    setY(uintToHex(bus.cpu.y,2));
    setStatus(uintToBin(bus.cpu.status,8));
    setSp(uintToHex(bus.cpu.sp,2));
    setClock(QString::number(bus.cpu.total_cycle_count,10));
    if(bus.cpu.operationLookup.count(bus.cpu.opcode)){
        setOpcode(QString::fromStdString( bus.cpu.operationLookup[bus.cpu.opcode].instruction_name ));
    } else {
        setOpcode(QString::number(bus.cpu.opcode ));
    }

}


