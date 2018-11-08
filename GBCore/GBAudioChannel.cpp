#include "GBAudioChannel.h"
#include "IGBAudioModule.h"
#include "GBAudioModule_Constant.h"
#include "GBAudioModule_FrequencySweeper.h"
#include "GBAudioModule_SquareWaveGenerator.h"
#include "GBAudioModule_RamWaveGenerator.h"
#include "GBAudioModule_NoiseWaveGenerator.h"
#include "GBAudioModule_LengthCounter.h"
#include "GBAudioModule_EnvelopeVolumeManager.h"

GBAudioChannel::GBAudioChannel(
        IGBAudioModule* frequencySweeper,
        IGBAudioModule* waveGenerator,
        IGBAudioModule* lengthCounter,
        IGBAudioModule* volumeManager)
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
                new GBAudioModule_FrequencySweeper(registers),
                new GBAudioModule_SquareWaveGenerator(registers),
                new GBAudioModule_LengthCounter(0x3F, registers),
                new GBAudioModule_EnvelopeVolumeManager(registers));
}

GBAudioChannel* GBAudioChannel::GetSquareChannel(quint8* registers)
{
    return new GBAudioChannel(
                new GBAudioModule_Constant(1),
                new GBAudioModule_SquareWaveGenerator(registers),
                new GBAudioModule_LengthCounter(0x3F, registers),
                new GBAudioModule_EnvelopeVolumeManager(registers));
}

GBAudioChannel* GBAudioChannel::GetWaveChannel(quint8* registers)
{
    return new GBAudioChannel(
                new GBAudioModule_Constant(1),
                new GBAudioModule_RamWaveGenerator(registers),
                new GBAudioModule_LengthCounter(0xFF, registers),
                new GBAudioModule_Constant(1));
}

GBAudioChannel* GBAudioChannel::GetNoiseChannel(quint8* registers)
{
    return new GBAudioChannel(
                new GBAudioModule_Constant(1),
                new GBAudioModule_NoiseWaveGenerator (registers),
                new GBAudioModule_LengthCounter(0x3F, registers),
                new GBAudioModule_EnvelopeVolumeManager(registers));
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
    if (IsSweepTick())
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
        m_VolumeManager->Tick();
    }
}
