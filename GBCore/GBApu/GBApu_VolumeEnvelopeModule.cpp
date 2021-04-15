#include "GBApu_VolumeEnvelopeModule.h"

void GBApu_VolumeEnvelopeModule::Reset()
{
    m_CurrentVolume = 0;
}

void GBApu_VolumeEnvelopeModule::Trigger()
{
    m_CurrentVolume = GetStartingVolume();
    m_Counter.Reload(GetPeriod());
}

void GBApu_VolumeEnvelopeModule::Tick(bool doAction, quint8 *sample)
{
    if (doAction)
    {
        m_Counter.Tick();
        if (m_Counter.IsZero())
        {
            m_Counter.Reload(GetPeriod());
            if (IsAddMode() && m_CurrentVolume < 0x0F)
            {
                m_CurrentVolume++;
            }
            else if (!IsAddMode() && m_CurrentVolume > 0)
            {
                m_CurrentVolume--;
            }
        }
    }
    if (*sample != 0)
    {
        *sample = m_CurrentVolume;
    }
}
