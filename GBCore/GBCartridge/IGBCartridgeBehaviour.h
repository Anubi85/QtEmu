#pragma once

#include <QtGlobal>

#define CARTRIDGE_REGISTER_MASK 0xE000
#define RAM_ENABLE_REQUEST 0x0000
#define ROM_BANK_SWITCH_REQUEST 0x2000
#define RAM_BANK_SWITCH_REQUEST 0x4000
#define SET_BANKING_MODE_REQUEST 0x6000

class GBBus;

class IGBCartridgeBehaviour
{
protected:
    quint8* m_Data;
    quint32 m_DataSize;
    IGBCartridgeBehaviour(quint8* data, quint32 size);
	bool IsRamEnableRequest(quint16 address) { return (address & CARTRIDGE_REGISTER_MASK) == RAM_ENABLE_REQUEST; }
	bool IsRomBankSwitchRequest(quint16 address) { return (address & CARTRIDGE_REGISTER_MASK) == ROM_BANK_SWITCH_REQUEST; }
	bool IsRamBankSwitchRequest(quint16 address) { return (address & CARTRIDGE_REGISTER_MASK) == RAM_BANK_SWITCH_REQUEST; }
	bool IsSetBankingModeRequest(quint16 address) { return  (address & CARTRIDGE_REGISTER_MASK) == SET_BANKING_MODE_REQUEST; }
public:
    virtual ~IGBCartridgeBehaviour() { delete[] m_Data; }
    virtual void ProcessRequests(GBBus* bus) = 0;
};
