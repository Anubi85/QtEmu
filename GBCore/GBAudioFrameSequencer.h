#ifndef GBAUDIOFRAMESEQUENCER_H
#define GBAUDIOFRAMESEQUENCER_H

#include <QtGlobal>

#define FRAME_SEQUENCER_DIVIDER 0x2000

class GBAudioFrameSequencer
{
private:
    quint16 m_TickCounter;
    quint8 m_FrameCounter;
public:
    GBAudioFrameSequencer();
    void Reset();
    void Tick();
    bool IsSweepTick() { return (m_FrameCounter & 0x03) == 0x02; }
};

#endif // GBAUDIOFRAMESEQUENCER_H
