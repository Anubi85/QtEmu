#include "GBInstructionContext.h"

GBInstructionContext::GBInstructionContext(quint8 opCode)
{
    m_x = (opCode & MASK_X) >> SHIFT_X;
    m_y = (opCode & MASK_Y) >> SHIFT_Y;
    m_z = (opCode & MASK_Z);
    m_w = (opCode & MASK_W) >> SHIFT_W;
    m_f = (opCode & MASK_F) != 0;
    m_q = (opCode & MASK_Q) >> SHIFT_Q;
    m_g = (opCode & MASK_G) != 0;
}
