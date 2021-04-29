#include "GBCpuState_Fetch.h"
#include "GBBus.h"
#include "IGBCpuStateContext.h"

quint16 GBCpuState_Fetch::s_InterruptRoutineAddress[INTERRUPT_NUM] =
{
    0x0040, //V-Blank
    0x0048, //LCD Status
    0x0050, //Timer Overflow
    0x0058, //Serial Transfer
    0x0060, //Hi-Lo of P10-P13
};

void GBCpuState_Fetch::Reset()
{
    m_Count = m_Context->GetCBFlag() ? 3 : 0;
}

void GBCpuState_Fetch::Update(GBBus* bus)
{
    if (--m_Count <= 0)
    {
        quint16 address = 0; //it will aways be override by the following code
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
        m_Context->SetCBFlag(m_Count == 0);
        //TODO: serve?
        m_Context->SetOpCode(NOP_INSTRUCTION);
        m_Context->SetState(CpuState::Decode);
    }
}
