#include "GBBus.h"
#include "GBApu_WaveChannel.h"
#include "GBApu_RamModule.h"
#include "GBApu_LengthCounterModule.h"
#include "GBApu_VolumeEnvelopeModule.h"

GBApu_WaveChannel::GBApu_WaveChannel(quint8& apuStatus, quint8 (&samplesRam)[AUDIO_RAM_SIZE]) :
    GBApu_ChannelBase(AUDIO_REG_ADDRESS_OFFSET + 2 * AUDIO_CHANNEL_REG_NUM, apuStatus)
{
    m_Modules[0] = nullptr;
    m_Modules[1] = new GBApu_RamModule(m_Registers, samplesRam);
    m_Modules[2] = new GBApu_LengthCounterModule(0xFF, AUDIO_CHANNEL3_ENABLE_MASK, m_ApuStatus, m_Registers);
    m_Modules[3] = new GBApu_VolumeEnvelopeModule(m_Registers);
}

void GBApu_WaveChannel::ReadRegister(GBBus *bus)
{
    switch (bus->GetAddress() - c_StartRegAddress)
    {
        case AUDIO_CHANNEL_NRX0_ADDRESS:
            bus->SetData(m_Registers[AUDIO_CHANNEL_NRX0_ADDRESS] | 0x7F);
            break;
        case AUDIO_CHANNEL_NRX1_ADDRESS:
            bus->SetData(0xFF);
            break;
        case AUDIO_CHANNEL_NRX2_ADDRESS:
            bus->SetData(m_Registers[AUDIO_CHANNEL_NRX2_ADDRESS] | 0x9F);
            break;
        case AUDIO_CHANNEL_NRX3_ADDRESS:
            bus->SetData(0xFF);
            break;
        case AUDIO_CHANNEL_NRX4_ADDRESS:
            bus->SetData(m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] | 0xBF);
            break;
        default:
            return;
    }
    bus->ReadReqAck();
}

void GBApu_WaveChannel::WriteRegister(GBBus *bus)
{
    switch (bus->GetAddress() - c_StartRegAddress)
    {
        case AUDIO_CHANNEL_NRX0_ADDRESS:
            //Not useed, do nothing
            break;
        case AUDIO_CHANNEL_NRX1_ADDRESS:
            m_Registers[AUDIO_CHANNEL_NRX1_ADDRESS] = bus->GetData();
            break;
        case AUDIO_CHANNEL_NRX2_ADDRESS:
            m_Registers[AUDIO_CHANNEL_NRX2_ADDRESS] = bus->GetData() & 0x60;
            break;
        case AUDIO_CHANNEL_NRX3_ADDRESS:
            m_Registers[AUDIO_CHANNEL_NRX3_ADDRESS] = bus->GetData();
            break;
        case AUDIO_CHANNEL_NRX4_ADDRESS:
            m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] = bus->GetData() & 0xC7;
            Trigger();
            break;
        default:
            return;
    }
    bus->WriteReqAck();
}
