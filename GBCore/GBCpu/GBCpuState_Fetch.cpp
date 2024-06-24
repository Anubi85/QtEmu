#include "GBCpuState_Fetch.h"
#include "GBBus.h"
#include "IGBCpuStateContext.h"

void GBCpuState_Fetch::Reset()
{
    m_Count = m_Context->GetCBFlag() ? 3 : 0;
}

void GBCpuState_Fetch::Update(GBBus* bus)
{
    if (--m_Count <= 0)
    {
        if (!m_Context->IsHandlingInterrupt())
        {
			bus->MainBus()->SetAddress(m_Context->GetPcAndIncrement());
			bus->MainBus()->RequestRead();
        }
        m_Context->SetState(CpuState::Decode);
    }
}
