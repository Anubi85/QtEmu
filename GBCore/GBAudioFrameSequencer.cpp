#include "GBAudioFrameSequencer.h"

GBAudioFrameSequencer::GBAudioFrameSequencer()
{
    Reset();
}

void GBAudioFrameSequencer::Reset()
{
    m_TickCounter = 0;
    m_FrameCounter = 0;
}

void GBAudioFrameSequencer::Tick()
{
    if((++m_TickCounter & (FRAME_SEQUENCER_DIVIDER - 1)) == 0)
    {
        m_FrameCounter++;
    }
}
