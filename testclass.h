#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "Bus.h"
#include <QObject>

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


private:
    QString m_name;
    QString m_accumulator;
    QString m_pc;
    QString m_x;
    QString m_y;
    QString m_status;
    QString m_opcode;
public:
    explicit TestClass(QObject *parent = nullptr);
    QString name();
    QString accumulator();
    QString pc();
    QString x();
    QString y();
    QString status();
    QString opcode();
    Bus bus;

signals:
    void nameChanged();
    void accumulatorChanged();
    void pcChanged();
    void xChanged();
    void yChanged();
    void statusChanged();
    void opcodeChanged();

public slots:
    void setname( QString );
    void setAccumulator( QString );
    void setPc( QString );
    void setX( QString );
    void setY( QString );
    void setStatus( QString );
    void setOpcode( QString );
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
