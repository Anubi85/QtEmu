#include "OpCode.h"

OpCode::OpCode(quint8 value)
{
    m_x = value & MASK_X >> SHIFT_X;
    m_y = value & MASK_Y >> SHIFT_Y;
    m_z = value & MASK_Z;
    m_w = value & MASK_W >> SHIFT_W;
    m_f = (value & MASK_F ) != 0;
}
