#include "GBAudioModule_EnvelopeVolumeManager.h"
#include "GBAudioCommonDefs.h"

GBAudioModule_EnvelopeVolumeManager::GBAudioModule_EnvelopeVolumeManager(quint8* registers) :
    IGBAudioModule(registers)
{

}

void GBAudioModule_EnvelopeVolumeManager::Reset()
{
    IGBAudioModule::Reset();
    m_Counter = m_Registers[AUDIO_CHANNEL_NR2_IDX] & 0x07;
    m_Sample = (m_Registers[AUDIO_CHANNEL_NR2_IDX] >> 4) & 0x0F;
    m_UpdateVolume = true;
}

void GBAudioModule_EnvelopeVolumeManager::Tick()
{
    if (m_UpdateVolume && (--m_Counter == 0))
    {
        m_Counter = m_Registers[AUDIO_CHANNEL_NR2_IDX] & 0x07;
        m_Sample += ((m_Registers[AUDIO_CHANNEL_NR2_IDX] & 0x80) != 0) ? 1 : -1;
        m_UpdateVolume = (m_Sample != 0x07) && (m_Sample != 0);
    }
}
