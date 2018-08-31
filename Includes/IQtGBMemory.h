#ifndef IQTGBMEMORY_H
#define IQTGBMEMORY_H

#include <QtCore/qglobal.h>

#ifdef QTGBMEMORY_LIBRARY
#define QTGBMEMORY_EXPORT Q_DECL_EXPORT
#else
#define QTGBMEMORY_EXPORT Q_DECL_IMPORT
#endif

class QTGBMEMORY_EXPORT IQtGBMemory
{
public:
    static IQtGBMemory* GetInstance();
    virtual ~IQtGBMemory();
    virtual bool LoadBios(QString biosFilePath) = 0;
    virtual bool IsBiosLoaded() = 0;
    virtual quint8 ReadByte(quint16 address) = 0;
    virtual quint16 ReadWord(quint16 address) = 0;
    virtual void WriteByte(quint16 address, quint8 value) = 0;
    virtual void WriteWord(quint16 address, quint16 value) = 0;
};

#endif // IQTGBMEMORY_H
