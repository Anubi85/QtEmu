#include "GBAudio.h"
#include "GBBus.h"

GBAudio::GBAudio() :
    m_Registers(AUDIO_MEMORY_SIZE, 0)
{
    Reset();
}

void GBAudio::Reset()
{
    GBComponent::Reset();
    m_Registers.fill(0);
    m_Registers[*AudioRegister::NR11] = static_cast<char>(0x80);
    m_Registers[*AudioRegister::NR12] = static_cast<char>(0xF3);
    m_Registers[*AudioRegister::NR50] = static_cast<char>(0x77);
    m_Registers[*AudioRegister::NR51] = static_cast<char>(0xF3);
    m_Registers[*AudioRegister::NR52] = static_cast<char>(0x81);
}

void GBAudio::Tick(GBBus* bus)
{
    AudioRegister reg;
    quint8 mask;
    //check if a read request is pending and the address is in range
    if (bus->IsReadReqPending() && IsAddressInRange(bus->GetAddress()))
    {
        reg = static_cast<AudioRegister>(bus->GetAddress() - AUDIO_ADDRESS_OFFSET);
        switch (reg)
        {
        case AudioRegister::NR11:
            mask = 0x3F;
            break;
        case AudioRegister::NR12:
            mask = 0x00;
            break;
        case AudioRegister::NR50:
            mask = 0x00;
            break;
        case AudioRegister::NR51:
            mask = 0x00;
            break;
        case AudioRegister::NR52:
            mask = 0x70;
            break;
        default:
            return;
        }
        bus->SetData(static_cast<quint8>(m_Registers[*reg]) | mask);
        bus->ReadReqAck();
    }
    //check if a write request is pending and the address is in range
    if (bus->IsWriteReqPending() && IsAddressInRange(bus->GetAddress()))
    {
        reg = static_cast<AudioRegister>(bus->GetAddress() - AUDIO_ADDRESS_OFFSET);
        switch (reg)
        {
        case AudioRegister::NR11:
            mask = 0xFF;
            break;
        case AudioRegister::NR12:
            mask = 0xFF;
            break;
        case AudioRegister::NR50:
            mask = 0xFF;
            break;
        case AudioRegister::NR51:
            mask = 0xFF;
            break;
        case AudioRegister::NR52:
            mask = 0x80;
            break;
        default:
            return;
        }
        m_Registers[*reg] = static_cast<char>(bus->GetData() & mask);
        bus->WriteReqAck();
    }
}
