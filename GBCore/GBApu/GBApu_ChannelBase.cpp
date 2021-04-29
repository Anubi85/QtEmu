#include "GBApu_ChannelBase.h"
#include "GBApu_ChannelModuleBase.h"
#include "GBApu_FrameSequencer.h"

GBApu_ChannelBase::GBApu_ChannelBase(quint8 channelMask, quint16 startRegAddress, quint8& apuStatus) :
    c_ChannelMask(channelMask),
    c_StartRegAddress(startRegAddress),
	m_ApuStatus(apuStatus)
{
	m_Dac = new GBApu_Dac(m_Sample);
    for (int i = 0; i < AUDIO_CHANNEL_MODULES_NUM; i++)
    {
        m_Modules[i] = nullptr;
    }
	Reset();
}

GBApu_ChannelBase::~GBApu_ChannelBase()
{
	delete m_Dac;
    for(int i = 0; i < AUDIO_CHANNEL_MODULES_NUM; i++)
    {
        if (m_Modules[i] != nullptr)
        {
            delete m_Modules[i];
        }
    }
}

void GBApu_ChannelBase::Reset()
{
	memset(m_Registers, 0, AUDIO_CHANNEL_REG_NUM);
	m_Sample = 0;
    for(int i = 0; i < AUDIO_CHANNEL_MODULES_NUM; i++)
    {
        if (m_Modules[i] != nullptr)
        {
            m_Modules[i]->Reset();
        }
    }
}

void GBApu_ChannelBase::Trigger()
{
    if ((m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] & 0x80) != 0)
    {
        for (int i = 0;  i < AUDIO_CHANNEL_MODULES_NUM; i++)
        {
            if (m_Modules[i] != nullptr)
            {
                m_Modules[i]->Trigger();
            }
        }
    }
}

void GBApu_ChannelBase::Tick(GBApu_FrameSequencer *sequencer)
{
    m_Sample = 0;
    if ((m_ApuStatus & c_ChannelMask) != 0)
    {
        for (int m = 0; m < AUDIO_CHANNEL_MODULES_NUM; m++)
        {
            if (m_Modules[m] != nullptr)
            {
                switch (m)
                {
                case 0:
                    m_Modules[m]->Tick(sequencer->IsFrequencySweepTick(), &m_Sample);
                    break;
                case 1:
                    m_Modules[m]->Tick(true, &m_Sample);
                    break;
                case 2:
                    m_Modules[m]->Tick(sequencer->IsLengthCounterTick(), &m_Sample);
                    break;
                case 3:
                    m_Modules[m]->Tick(sequencer->IsVolumeEnvelopeTick(), &m_Sample);
                    break;
                }
            }
        }
    }
}
