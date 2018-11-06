#include "GBVolumeManager_Envelope.h"
#include "GBAudioCommonDefs.h"

GBVolumeManager_Envelope::GBVolumeManager_Envelope(quint8* registers) :
    IGBVolumeManager(registers)
{

}

void GBVolumeManager_Envelope::Reset()
{
    IGBVolumeManager::Reset();
    m_Counter = m_Registers[AUDIO_CHANNEL_NR2_IDX] & 0x07;
    m_Volume = (m_Registers[AUDIO_CHANNEL_NR2_IDX] >> 4) & 0x0F;
    m_UpdateVolume = true;
    m_IsEnabled = true; //always enabled
}

void GBVolumeManager_Envelope::Tick(quint8 sample)
{
    if (m_UpdateVolume && (--m_Counter == 0))
    {
        m_Counter = m_Registers[AUDIO_CHANNEL_NR2_IDX] & 0x07;
        m_Volume += ((m_Registers[AUDIO_CHANNEL_NR2_IDX] & 0x80) != 0) ? 1 : -1;
        m_UpdateVolume = (m_Volume != 0x07) && (m_Volume != 0);
    }
    m_Sample = sample * m_Volume;
}
