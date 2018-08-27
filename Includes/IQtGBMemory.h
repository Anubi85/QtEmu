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
    virtual uchar ReadByte(ushort address) = 0;
    virtual ushort ReadWord(ushort address) = 0;
	virtual void WriteByte(ushort address, uchar value) = 0;
	virtual void WriteWord(ushort address, ushort value) = 0;
};

#endif // IQTGBMEMORY_H
