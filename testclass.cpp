#include "testclass.h"
#include <QDebug>

TestClass::TestClass(QObject *parent)
    : QObject{parent}
{
    m_name = "Test";
    bus.cpu.write(0x0000,0xA5);
    bus.cpu.write(0x0001,0xF9);
    bus.cpu.write(0x0002,0xE5);
    bus.cpu.write(0x0003,0xFF);
    bus.cpu.write(0x00F9,0xFF);
    bus.cpu.write(0x00FF,0x7F);
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

void TestClass::activateClock()
{
    bus.cpu.clockByInstruction();
    setAccumulator(uintToHex(bus.cpu.a,2));
    setPc(uintToHex(bus.cpu.pc,4));
    setX(uintToHex(bus.cpu.x,2));
    setY(uintToHex(bus.cpu.y,2));
    setStatus(uintToBin(bus.cpu.status,8));
    setOpcode(QString::fromStdString( bus.cpu.operationLookup[bus.cpu.opcode].instruction_name ));
}


