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
        quint8 enableBitMask,
        quint8* channelsState,
        IGBAudioModule* frequencySweeper,
        IGBAudioModule* waveGenerator,
        IGBAudioModule* lengthCounter,
        IGBAudioModule* volumeManager) :
    c_EnableBitMask(enableBitMask)
{
    m_ChannelsState = channelsState;
    m_FrequencySweeper = frequencySweeper;
    m_WaveGenerator = waveGenerator;
    m_LengthCounter = lengthCounter;
    m_VolumeManager = volumeManager;
    Reset();
}

GBAudioChannel::~GBAudioChannel()
{
    delete m_FrequencySweeper;
    delete m_WaveGenerator;
    delete m_LengthCounter;
    delete m_VolumeManager;
}

GBAudioChannel* GBAudioChannel::GetSweepSquareChannel(quint8 enableBitMask, quint8* channelsState, quint8* registers)
{
    return new GBAudioChannel(
                enableBitMask,
                channelsState,
                new GBAudioModule_FrequencySweeper(registers),
                new GBAudioModule_SquareWaveGenerator(registers),
                new GBAudioModule_LengthCounter(0x3F, registers),
                new GBAudioModule_EnvelopeVolumeManager(registers));
}

GBAudioChannel* GBAudioChannel::GetSquareChannel(quint8 enableBitMask, quint8* channelsState, quint8* registers)
{
    return new GBAudioChannel(
                enableBitMask,
                channelsState,
                new GBAudioModule_Constant(1),
                new GBAudioModule_SquareWaveGenerator(registers),
                new GBAudioModule_LengthCounter(0x3F, registers),
                new GBAudioModule_EnvelopeVolumeManager(registers));
}

GBAudioChannel* GBAudioChannel::GetWaveChannel(quint8 enableBitMask, quint8* channelsState, quint8* registers, quint8* samplesRam)
{
    return new GBAudioChannel(
                enableBitMask,
                channelsState,
                new GBAudioModule_Constant(1),
                new GBAudioModule_RamWaveGenerator(registers, samplesRam),
                new GBAudioModule_LengthCounter(0xFF, registers),
                new GBAudioModule_Constant(1));
}

GBAudioChannel* GBAudioChannel::GetNoiseChannel(quint8 enableBitMask, quint8* channelsState, quint8* registers)
{
    return new GBAudioChannel(
                enableBitMask,
                channelsState,
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

void GBAudioChannel::Trigger()
{
    EnableChannel();
    m_FrequencySweeper->Trigger();
    m_WaveGenerator->Trigger();
    m_LengthCounter->Trigger();
    m_VolumeManager->Trigger();
}

void GBAudioChannel::PerformModuleTick(bool condition, IGBAudioModule* module)
{
    if (condition && IsChannelEnabled())
    {
        module->Tick();
        if (!module->IsEnabled())
        {
            DisableChannel();
        }
    }
}

void GBAudioChannel::Tick()
{
    m_TickCounter++;
    PerformModuleTick(IsSweepTick(), m_FrequencySweeper);
    PerformModuleTick(true, m_WaveGenerator);
    PerformModuleTick(IsLengthCounterTick(), m_LengthCounter);
    PerformModuleTick(IsVolumeManagerTick(), m_VolumeManager);
}

qreal GBAudioChannel::GetSample()
{
    if (IsChannelEnabled())
    {
        return (m_FrequencySweeper->GetSample() * m_WaveGenerator->GetSample() * m_LengthCounter->GetSample() * m_VolumeManager->GetSample()) * DAC_FACTOR + DAC_OFFSET;
    }
    else
    {
        return 0.0;
    }
}
