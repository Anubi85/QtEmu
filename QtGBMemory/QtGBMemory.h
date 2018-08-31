#ifndef QTGBMEMORY_H
#define QTGBMEMORY_H

#include "IQtGBMemory.h"
#include <QByteArray>

#define BIOS_SIZE 256

class QtGBMemory : public IQtGBMemory
{
private:
    bool m_IsBiosLoaded;
    QByteArray m_Bios;
public:
    QtGBMemory();
    bool LoadBios(QString biosFilePath) override;
    bool IsBiosLoaded() override { return m_IsBiosLoaded; }
    quint8 ReadByte(quint16 address) override;
    quint16 ReadWord(quint16 address) override;
    void WriteByte(quint16 address, quint8 value) override;
    void WriteWord(quint16 address, quint16 value) override;
};

#endif // QTGBMEMORY_H
