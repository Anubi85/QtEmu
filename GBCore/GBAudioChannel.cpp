#include "GBAudioChannel.h"
#include "IGBAudioChannelContext.h"
#include "GBFrequencySweeper.h"
#include "IGBWaveGenerator.h"
#include "GBLengthCounter.h"

GBAudioChannel::GBAudioChannel(IGBAudioChannelContext* context, GBFrequencySweeper* frequencySweeper, IGBWaveGenerator* waveGenerator, GBLengthCounter* lengthCounter)
{
    m_Context = context;
    m_FrequencySweeper = frequencySweeper;
    m_WaveGenerator = waveGenerator;
    m_LengthCounter = lengthCounter;
}

GBAudioChannel::~GBAudioChannel()
{
    delete m_FrequencySweeper;
    delete m_WaveGenerator;
    delete  m_LengthCounter;
}

void GBAudioChannel::Reset()
{
    m_TickCounter = 0;
    m_FrequencySweeper->Reset();
    m_WaveGenerator->Reset();
    m_LengthCounter->Reset();
}

void GBAudioChannel::Tick()
{
    m_TickCounter++;
    if ((m_FrequencySweeper != nullptr) && IsSweepTick())
    {
        m_FrequencySweeper->Tick();
    }
    m_WaveGenerator->Tick();
    if (IsLengthCounterTick())
    {
        m_LengthCounter->Tick();
    }
}
