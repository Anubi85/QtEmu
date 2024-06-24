#pragma once

#include <QtGlobal>
#include <QString>

enum class Error : quint16
{
    Ok = 0x0000,
	MAINBUS_ReadRequestNotServed = 0x0001,
	MAINBUS_WriteRequestNotServed = 0x0002,
	DMABUS_ReadRequestNotServed = 0x0003,
	DMABUS_WriteRequestNotServed = 0x0004,
    CPU_OpCodeNotImplemented = 0x0101,
    CPU_UnespectedOpCodeStep = 0x0102,
    BIOS_FileNotFound = 0x0201,
    BIOS_FailToOpen = 0x0202,
    BIOS_WrongFileSize = 0x0203,
    BIOS_WrongFileMD5 = 0x0204,
    ROM_FileNotFound = 0x0501,
    ROM_FailToOpen = 0x0502,
};

enum class Component
{
    CPU,
    BIOS,
    RAM,
    Cartridge,
    GPU,
    APU,
    Serial,
	UnusedIO,
    InternalRAM,
	Interrupt,
    Total
};

class GBBus;

class GBComponent
{
protected:
    Error m_ErrorCode;
public:
    GBComponent() { Reset(); }
    virtual ~GBComponent() { }
    bool HasError() { return m_ErrorCode != Error::Ok; }
    virtual void Reset() { m_ErrorCode = Error::Ok; }
	virtual void Tick(GBBus* bus) = 0;
    quint16 GetLastError() { return static_cast<quint16>(m_ErrorCode); }
    QString GetErrorDescription(quint16 errorCode) { return GetErrorDescription(static_cast<Error>(errorCode)); }
    QString GetErrorDescription(Error error);
};
