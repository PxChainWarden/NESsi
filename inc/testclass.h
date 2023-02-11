#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "Bus.h"
#include <QObject>

#pragma once
#include <array>

#include <QList>
#include <QVariantList>

class pixelData{
    Q_GADGET
public:
    pixelData(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
    pixelData(){
    }

        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
        Q_PROPERTY(uint8_t r MEMBER r);
        Q_PROPERTY(uint8_t g MEMBER g);
        Q_PROPERTY(uint8_t b MEMBER b);
        Q_PROPERTY(uint8_t a MEMBER a);
    };

class TestClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setname NOTIFY nameChanged)
    Q_PROPERTY(QString accumulator READ accumulator WRITE setAccumulator NOTIFY accumulatorChanged)
    Q_PROPERTY(QString pc READ pc WRITE setPc NOTIFY pcChanged)
    Q_PROPERTY(QString x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(QString y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(QString opcode READ opcode WRITE setOpcode NOTIFY opcodeChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString sp READ sp WRITE setSp NOTIFY spChanged)
    Q_PROPERTY(QString clock READ clock WRITE setClock NOTIFY clockChanged)

    Q_PROPERTY(pixelData palette READ palette WRITE setPalette NOTIFY paletteChanged)
    Q_PROPERTY(QVariantList frame READ frame NOTIFY frameChanged)
    Q_PROPERTY(QVariantList patternLeft READ patternLeft NOTIFY patternLeftChanged)
    Q_PROPERTY(QVariantList patternRight READ patternRight NOTIFY patternRightChanged)
    Q_PROPERTY(int changePalette READ changePalette NOTIFY changePaletteChanged)



private:
    QString m_name;
    QString m_accumulator;
    QString m_pc;
    QString m_sp;
    QString m_x;
    QString m_y;
    QString m_status;
    QString m_opcode;
    QString m_clock;

    int m_palette_index = 0;

    QVariantList m_frame;

    int index = 0;



    std::array< pixelData, 0x40> m_palette;

public:
    explicit TestClass(QObject *parent = nullptr);
    QString name();
    QString accumulator();
    QString pc();
    QString sp();
    QString x();
    QString y();
    QString status();
    QString opcode();
    QString clock();
    pixelData palette();
    QVariantList frame();
    QVariantList pattern(int i);
    QVariantList patternLeft();
    QVariantList patternRight();
    int changePalette();
    Bus bus;

signals:
    void nameChanged();
    void accumulatorChanged();
    void pcChanged();
    void spChanged();
    void xChanged();
    void yChanged();
    void statusChanged();
    void opcodeChanged();
    void clockChanged();
    void paletteChanged();
    void frameChanged();
    void patternLeftChanged();
    void patternRightChanged();
    void changePaletteChanged();

public slots:
    void setname( QString );
    void setAccumulator( QString );
    void setPc( QString );
    void setSp( QString );
    void setX( QString );
    void setY( QString );
    void setStatus( QString );
    void setOpcode( QString );
    void setClock( QString );
    void setPalette( pixelData );
    void activateClock();

    QString uintToHex(uint num, int format){
        QString hex = QString::number(num,16).toUpper();
        int len = hex.length();
        QString formatting = "0x";
        for(int index = len; index < format; index++ ){
            formatting.append("0");
        }

        return formatting+hex;
    }

    QString uintToBin(uint num, int format){
        QString bin = QString::number(num,2);
        int len = bin.length();
        QString formatting = "";
        for(int index = len; index < format; index++ ){
            formatting.append("0");
        }

        return formatting+bin;
    }

};

#endif // TESTCLASS_H
