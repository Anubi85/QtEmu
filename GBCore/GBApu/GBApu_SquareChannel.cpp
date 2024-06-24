#include "GBInternalBus.h"
#include "GBApu_SquareChannel.h"
#include "GBApu_SquareWaveModule.h"
#include "GBApu_LengthCounterModule.h"
#include "GBApu_VolumeEnvelopeModule.h"

GBApu_SquareChannel::GBApu_SquareChannel(quint8& apuStatus) :
	GBApu_ChannelBase(AUDIO_CHANNEL2_ENABLE_MASK, APU_REGISTERS_ADDRESS + AUDIO_CHANNEL_REG_NUM, apuStatus)
{
    m_Modules[0] = nullptr;
    m_Modules[1] = new GBApu_SquareWaveModule(m_Registers);
    m_Modules[2] = new GBApu_LengthCounterModule(0x3F, c_ChannelMask, m_ApuStatus, m_Registers);
    m_Modules[3] = new GBApu_VolumeEnvelopeModule(m_Registers);
}

void GBApu_SquareChannel::ReadRegister(IGBBus* bus)
{
	switch (bus->GetAddress())
    {
		case NR20_REGISTER:
            bus->SetData(0xFF);
            break;
		case NR21_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(c_StartRegAddress)] | 0x3F);
            break;
		case NR22_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(c_StartRegAddress)]);
            break;
		case NR23_REGISTER:
            bus->SetData(0xFF);
            break;
		case NR24_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(c_StartRegAddress)] | 0xBF);
            break;
        default:
            return;
    }
    bus->ReadReqAck();
}

void GBApu_SquareChannel::WriteRegister(IGBBus* bus)
{
    switch (bus->GetAddress() - c_StartRegAddress)
    {
		case NR20_REGISTER:
            //Not useed, do nothing
            break;
		case NR21_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData();
            break;
		case NR22_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData();
            break;
		case NR23_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData();
            break;
		case NR24_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData() & 0xC7;
            Trigger();
            break;
        default:
            return;
    }
    bus->WriteReqAck();
}
