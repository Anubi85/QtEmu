#include "GBCpuState_Fetch.h"
#include "GBBus.h"
#include "IGBCpuStateContext.h"

void GBCpuState_Fetch::Reset()
{
    m_Count = m_Context->GetCBFlag() ? 3 : 0;
}

void GBCpuState_Fetch::Update(GBBus* bus, GBInterruptBus* interruptBus)
{
    Q_UNUSED(interruptBus)
    if (--m_Count <= 0)
    {
        if (!m_Context->IsHandlingInterrupt())
        {
            quint16 address = m_Context->GetPcAndIncrement();
            bus->SetAddress(address);
            bus->RequestRead();
        }
        m_Context->SetState(CpuState::Decode);
    }
}
