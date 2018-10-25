#include "GBAudioChannelBase.h"
#include "GBBus.h"

GBAudioChannelBase::GBAudioChannelBase(quint16 addressOffset) :
    c_RegisterAddressOffset (addressOffset)
{
    Reset();
}

GBAudioChannelBase::~GBAudioChannelBase() {}

void GBAudioChannelBase::Reset()
{
    m_Enabled = false;
    m_LengthCounterEnabled = false;
    m_Frequency = 0;
    m_FrequencyCounter = 0;
    m_Cycles = 0;
    m_AudioCycles = 0;
    m_BaseAudioSample = 0;
}

void GBAudioChannelBase::Tick(GBBus* bus)
{
    //check if read request is pending
    if (bus->IsReadReqPending())
    {
        if (IsAddressInRegisterRange(bus->GetAddress()))
        {
            switch (static_cast<AudioChannelRegister>(bus->GetAddress() - c_RegisterAddressOffset))
            {
            case AudioChannelRegister::NRx0:
                bus->SetData(ReadNRx0());
                break;
            case AudioChannelRegister::NRx1:
                bus->SetData(ReadNRx1());
                break;
            case AudioChannelRegister::NRx2:
                bus->SetData(ReadNRx2());
                break;
            case AudioChannelRegister::NRx3:
                bus->SetData(ReadNRx3());
                break;
            case AudioChannelRegister::NRx4:
                bus->SetData(ReadNRx4());
                break;
            }
            bus->ReadReqAck();
        }
        else
        {
            ProcessReadRequest(bus);
        }
    }
    //check if write request is pending
    if (bus->IsWriteReqPending())
    {
        if (IsAddressInRegisterRange(bus->GetAddress()))
        {
            switch (static_cast<AudioChannelRegister>(bus->GetAddress() - c_RegisterAddressOffset))
            {
            case AudioChannelRegister::NRx0:
                WriteNRx0(bus->GetData());
                break;
            case AudioChannelRegister::NRx1:
                WriteNRx1(bus->GetData());
                break;
            case AudioChannelRegister::NRx2:
                WriteNRx2(bus->GetData());
                break;
            case AudioChannelRegister::NRx3:
                WriteNRx3(bus->GetData());
                break;
            case AudioChannelRegister::NRx4:
                WriteNRx4(bus->GetData());
                break;
            }
            bus->WriteReqAck();
        }
        else
        {
            ProcessWriteRequest(bus);
        }
    }
    //process audio modules
    ++m_Cycles &= AUDIO_CHANNEL_FREQUENCY_RATIO;
    if (m_Cycles == 0)
    {
        ++m_AudioCycles &= 0x7;
        ProcessModules();
    }
}
