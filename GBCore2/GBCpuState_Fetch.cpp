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

GBCpuState_Fetch::GBCpuState_Fetch(GBCpu* context) :
    IGBCpuState (context)
{

}

void GBCpuState_Fetch::Update(GBBus* bus)
{
    quint16 address;
    //manage interrupts
    if (m_Context->m_IsInterruptEnabled && bus->GetData() != 0)
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
        address = m_Context->m_PC++;
    }
    bus->SetAddress(address);
    bus->RequestRead();
    m_Context->SetState(new GBCpuState_Decode(m_Context, false));
}
