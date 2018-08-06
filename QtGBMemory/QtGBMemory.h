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
    uchar ReadByte(ushort address) override;
    ushort ReadWord(ushort address) override;
};

#endif // QTGBMEMORY_H
