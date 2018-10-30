#include "GBAudioChannel.h"
#include "IGBAudioChannelContext.h"
#include "IGBWaveGenerator.h"

GBAudioChannel::GBAudioChannel(IGBAudioChannelContext* context, IGBWaveGenerator* waveGenerator)
{
    m_Context = context;
    m_WaveGenerator = waveGenerator;
}

GBAudioChannel::~GBAudioChannel()
{
    delete m_WaveGenerator;
}

void GBAudioChannel::Reset()
{
    m_WaveGenerator->Reset();
}

void GBAudioChannel::Tick()
{
    m_WaveGenerator->Tick(false);
}
