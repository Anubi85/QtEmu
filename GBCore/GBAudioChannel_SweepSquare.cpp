#include "GBAudioChannel_SweepSquare.h"
#include "GBBus.h"

GBAudioChannel_SweepSquare::GBAudioChannel_SweepSquare()
{

}

quint8 GBAudioChannel_SweepSquare::ReadRegister(AudioChannelRegister reg)
{
    switch (reg)
    {
    case AudioChannelRegister::NRx0:
        return m_Registers[*AudioChannelRegister::NRx0] | 0x80;
    case AudioChannelRegister::NRx1:
        return m_Registers[*AudioChannelRegister::NRx1] | 0x3F;
    case AudioChannelRegister::NRx2:
        return m_Registers[*AudioChannelRegister::NRx2];
    case AudioChannelRegister::NRx3:
        return 0xFF; //read only register
    case AudioChannelRegister::NRx4:
        return m_Registers[*AudioChannelRegister::NRx4] | 0xBF;
    }
}

void GBAudioChannel_SweepSquare::WriteRegister(AudioChannelRegister reg, quint8 value)
{
    switch (reg)
    {
    case AudioChannelRegister::NRx0:
        m_Registers[*AudioChannelRegister::NRx0] = value & 0x7F;
        break;
    case AudioChannelRegister::NRx1:
        m_Registers[*AudioChannelRegister::NRx1] = value;
        break;
    case AudioChannelRegister::NRx2:
        m_Registers[*AudioChannelRegister::NRx2] = value;
        break;
    case AudioChannelRegister::NRx3:
        m_Registers[*AudioChannelRegister::NRx3] = value;
        break;
    case AudioChannelRegister::NRx4:
        m_Registers[*AudioChannelRegister::NRx4] = value & 0xC7;
        break;
    }
}

void GBAudioChannel_SweepSquare::Tick(GBBus* bus)
{
    if (IsAddressInRange(bus->GetAddress()))
    {
        if (bus->IsReadReqPending())
        {
            bus->SetData(ReadRegister(static_cast<AudioChannelRegister>(bus->GetAddress() - SWEEP_SQUARE_CHANNEL_ADDRESS_OFFSET)));
            bus->ReadReqAck();
        }
        if (bus->IsWriteReqPending())
        {
            WriteRegister(static_cast<AudioChannelRegister>(bus->GetAddress() - SWEEP_SQUARE_CHANNEL_ADDRESS_OFFSET), bus->GetData());
            bus->WriteReqAck();
        }
    }
}
