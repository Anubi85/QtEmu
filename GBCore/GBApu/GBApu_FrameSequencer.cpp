#include "GBApu_FrameSequencer.h"

void GBApu_FrameSequencer::Reset()
{
    m_LengthCounter.Reload(0);
    m_VolumeCounter.Reload(VOLUME_COUNT);
    m_FrequencyCounter.Reload(FREQUENCY_COUNT / 4 * 3);
}

void GBApu_FrameSequencer::Tick()
{
    if (m_LengthCounter.IsZero())
    {
        m_LengthCounter.Reload(LENGTH_COUNT);
    }
    if (m_VolumeCounter.IsZero())
    {
        m_VolumeCounter.Reload(VOLUME_COUNT);
    }
    if (m_FrequencyCounter.IsZero())
    {
        m_FrequencyCounter.Reload(FREQUENCY_COUNT);
    }
    m_LengthCounter.Tick();
    m_VolumeCounter.Tick();
    m_FrequencyCounter.Tick();
}
