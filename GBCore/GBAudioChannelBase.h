#ifndef GBAUDIOCHANNELBASE_H
#define GBAUDIOCHANNELBASE_H

#include <QtGlobal>
#include "GBUtils.h"

#define AUDIO_CHANNEL_REG_SIZE 5

enum class AudioChannelRegister
{
    NRx0 = 0,
    NRx1 = 1,
    NRx2 = 2,
    NRx3 = 3,
    NRx4 = 4,
};

class GBBus;

class GBAudioChannelBase
{
private:
    const quint16 c_RegisterAddressOffset;

    bool IsAddressInRegisterRange(quint16 address) { return address >= c_RegisterAddressOffset && address < (c_RegisterAddressOffset + AUDIO_CHANNEL_REG_SIZE); }
protected:
    bool m_Enabled;
    bool m_LengthCounterEnabled;
    quint16 m_Frequency;
    quint16 m_FrequencyTimer;
    quint8 m_LengthCount;

    GBAudioChannelBase(quint16 addressOffset);
    virtual void ProcessReadRequest(GBBus* bus) { Q_UNUSED(bus) }
    virtual quint8 ReadNRx0() { return 0xFF; }
    virtual quint8 ReadNRx1() { return 0xFF; }
    virtual quint8 ReadNRx2() { return 0xFF; }
    virtual quint8 ReadNRx3() { return 0xFF; }
    virtual quint8 ReadNRx4() { return 0xFF; }
    virtual void ProcessWriteRequest(GBBus* bus) { Q_UNUSED(bus) }
    virtual void WriteNRx0(quint8 value) { Q_UNUSED(value) }
    virtual void WriteNRx1(quint8 value) { Q_UNUSED(value) }
    virtual void WriteNRx2(quint8 value) { Q_UNUSED(value) }
    virtual void WriteNRx3(quint8 value) { Q_UNUSED(value) }
    virtual void WriteNRx4(quint8 value) { Q_UNUSED(value) }
    virtual void ProcessModules() = 0;
public:
    virtual ~GBAudioChannelBase();
    void Tick(GBBus* bus);
    virtual void Reset();
};

#endif // GBAUDIOCHANNELBASE_H
