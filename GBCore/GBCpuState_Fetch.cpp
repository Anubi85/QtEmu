#include "GBCpuState_Fetch.h"
#include "GBCpuState_Decode.h"
#include "GBBus.h"
#include "GBCpu.h"

quint16 GBCpuState_Fetch::s_InterruptRoutineAddress[INTERRUPT_NUM] =
{
    0x0040, //V-Blank
    0x0048, //LCD Status
    0x0050, //Timer Overflow
    0x0058, //Serial Transfer
    0x0060, //Hi-Lo of P10-P13
};

GBCpuState_Fetch::GBCpuState_Fetch(GBCpu* context, bool isCB) :
    IGBCpuState (context)
{
    m_Count = isCB ? 3 : 0;
}

void GBCpuState_Fetch::Update(GBBus* bus)
{
    if (--m_Count <= 0)
    {
        quint16 address;
        //manage interrupts
        if (m_Count != 0 && m_Context->GetImeFlag() && bus->GetData() != 0)
        {
            for (int mask = 0x01, idx = 0; idx < INTERRUPT_NUM; idx ++, mask <<= idx)
            {
                if ((bus->GetData() & mask) != 0)
                {
                    address = s_InterruptRoutineAddress[idx];
                    break;
                }
            }
        }
        else
        {
            address = m_Context->GetPcAndIncrement();
        }
        bus->SetAddress(address);
        bus->RequestRead();
        m_Context->SetState(new GBCpuState_Decode(m_Context, m_Count == 0));
    }
}
