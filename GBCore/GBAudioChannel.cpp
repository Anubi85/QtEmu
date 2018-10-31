#include "GBAudioChannel.h"
#include "IGBAudioChannelContext.h"
#include "GBFrequencySweeper.h"
#include "IGBWaveGenerator.h"

GBAudioChannel::GBAudioChannel(IGBAudioChannelContext* context, GBFrequencySweeper* frequencySweeper, IGBWaveGenerator* waveGenerator)
{
    m_Context = context;
    m_FrequencySweeper = frequencySweeper;
    m_WaveGenerator = waveGenerator;
}

GBAudioChannel::~GBAudioChannel()
{
    delete m_FrequencySweeper;
    delete m_WaveGenerator;
}

void GBAudioChannel::Reset()
{
    m_FrequencySweeper->Reset();
    m_WaveGenerator->Reset();
}

void GBAudioChannel::Tick(bool isSweepTick)
{
    if ((m_FrequencySweeper != nullptr) && isSweepTick)
    {
        quint16 frequency = 0;
        m_FrequencySweeper->Tick(0x00, &frequency);
    }
    m_WaveGenerator->Tick(false);
}
