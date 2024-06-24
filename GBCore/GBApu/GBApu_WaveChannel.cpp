#include "GBInternalBus.h"
#include "GBApu_WaveChannel.h"
#include "GBApu_RamModule.h"
#include "GBApu_LengthCounterModule.h"
#include "GBApu_VolumeEnvelopeModule.h"

GBApu_WaveChannel::GBApu_WaveChannel(quint8& apuStatus, quint8 (&samplesRam)[APU_RAM_SIZE]) :
	GBApu_ChannelBase(AUDIO_CHANNEL3_ENABLE_MASK, APU_REGISTERS_ADDRESS + 2 * AUDIO_CHANNEL_REG_NUM, apuStatus)
{
    m_Modules[0] = nullptr;
    m_Modules[1] = new GBApu_RamModule(m_Registers, samplesRam);
    m_Modules[2] = new GBApu_LengthCounterModule(0xFF, c_ChannelMask, m_ApuStatus, m_Registers);
    m_Modules[3] = new GBApu_VolumeEnvelopeModule(m_Registers);
}

void GBApu_WaveChannel::ReadRegister(IGBBus* bus)
{
	switch (bus->GetAddress())
    {
		case NR30_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(c_StartRegAddress)] | 0x7F);
            break;
		case NR31_REGISTER:
            bus->SetData(0xFF);
            break;
		case NR32_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(c_StartRegAddress)] | 0x9F);
            break;
		case NR33_REGISTER:
            bus->SetData(0xFF);
            break;
		case NR34_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(c_StartRegAddress)] | 0xBF);
            break;
        default:
            return;
    }
    bus->ReadReqAck();
}

void GBApu_WaveChannel::WriteRegister(IGBBus* bus)
{
	switch (bus->GetAddress())
    {
		case NR30_REGISTER:
            //Not useed, do nothing
            break;
		case NR31_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData();
			break;
		case NR32_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData() & 0x60;
            break;
		case NR33_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData();
            break;
		case NR34_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData() & 0xC7;
            Trigger();
            break;
        default:
            return;
    }
    bus->WriteReqAck();
}
