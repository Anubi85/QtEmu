#include "GBCpuState_InterruptCheck.h"

quint16 GBCpuState_InterruptCheck::s_InterruptRoutineAddress[INTERRUPT_NUM] =
{
    0x0040, //V-Blank
    0x0048, //LCD Status
    0x0050, //Timer Overflow
    0x0058, //Serial Transfer
    0x0060, //Hi-Lo of P10-P13
};
