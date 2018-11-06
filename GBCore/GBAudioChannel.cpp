#include "GBAudioChannel.h"
#include "GBFrequencySweeper.h"
#include "IGBWaveGenerator.h"
#include "GBWaveGenerator_Square.h"
#include "GBLengthCounter.h"
#include "IGBVolumeManager.h"
#include "GBVolumeManager_Envelope.h"

GBAudioChannel::GBAudioChannel(
        GBFrequencySweeper* frequencySweeper,
        IGBWaveGenerator* waveGenerator,
        GBLengthCounter* lengthCounter,
        IGBVolumeManager* volumeManager)
{
    m_FrequencySweeper = frequencySweeper;
    m_WaveGenerator = waveGenerator;
    m_LengthCounter = lengthCounter;
    m_VolumeManager = volumeManager;
}

GBAudioChannel::~GBAudioChannel()
{
    delete m_FrequencySweeper;
    delete m_WaveGenerator;
    delete m_LengthCounter;
    delete m_VolumeManager;
}

GBAudioChannel* GBAudioChannel::GetSweepSquareChannel(quint8* registers)
{
    return new GBAudioChannel(
                new GBFrequencySweeper(registers),
                new GBWaveGenerator_Square(registers),
                new GBLengthCounter(0x3F, registers),
                new GBVolumeManager_Envelope(registers));
}

GBAudioChannel* GBAudioChannel::GetSquareChannel(quint8* registers)
{
    return new GBAudioChannel(
                nullptr,
                new GBWaveGenerator_Square(registers),
                new GBLengthCounter(0x3F, registers),
                new GBVolumeManager_Envelope(registers));
}

void GBAudioChannel::Reset()
{
    m_TickCounter = 0;
    m_FrequencySweeper->Reset();
    m_WaveGenerator->Reset();
    m_LengthCounter->Reset();
    m_VolumeManager->Reset();
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
    if (IsVolumeManagerTick())
    {
        m_VolumeManager->Tick(m_WaveGenerator->GetSample());
    }
}
