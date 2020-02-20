#include "GBApu_LfsrModule.h"

void GBApu_LfsrModule::Reset()
{
    GBApu_ChannelModuleBase::Reset();
    m_LFSR = 0;
    m_FrequencyCounter.Reload(GetFrequency());
}

void GBApu_LfsrModule::Trigger()
{
    m_LFSR = 0x7FFF;
    m_FrequencyCounter.Reload(GetFrequency());
}

void GBApu_LfsrModule::Tick(bool doAction, quint8 *sample)
{
    Q_UNUSED(doAction)
    m_FrequencyCounter.Tick();
    if (m_FrequencyCounter.IsZero())
    {
        m_FrequencyCounter.Reload(GetFrequency());
        quint16 cleanMask = Is7BitShift() ? 0x3FBF : 0x3FFF;
        quint16 dataMask = 0x0000;
        switch (m_LFSR & 0x0003)
        {
        case 0b01:
        case 0b10:
            dataMask = Is7BitShift() ? 0x4040 : 0x4000;
            break;
        }
        m_LFSR >>= 1;
        m_LFSR &= cleanMask;
        m_LFSR |= dataMask;
    }
    *sample = (~m_LFSR & 0x0001);
}

quint16 GBApu_LfsrModule::GetFrequency()
{
    quint8 divisorCode = GetDivisorCode();
    quint16 frequency = divisorCode == 0 ? 8 : (16 * divisorCode);
    frequency <<= GetDivisorShift();
    return frequency;
}
