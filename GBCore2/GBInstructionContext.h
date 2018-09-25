#ifndef GBINSTRUCTIONCONTEXT_H
#define GBINSTRUCTIONCONTEXT_H

#include <QtCore>
#include "GBUtils.h"

/* Opcode bits
 * +-+-+-+-+-+-+-+-+
 * |7|6|5|4|3|2|1|0|
 * +-+-+-+-+-+-+-+-+
 * |x|x|y|y|y|z|z|z|
 * +-+-+-+-+-+-+-+-+
 * | | |w|w|f| | | |
 * +-+-+-+-+-+-+-+-+
 * | | |g|q|q| | | |
 * +-+-+-+-+-+-+-+-+
*/

#define BYTE_SIZE 8

#define MASK_X 0xC0
#define MASK_Y 0x38
#define MASK_Z 0x07
#define MASK_W 0x30
#define MASK_Q 0x18

#define SHIFT_X 6
#define SHIFT_Y 3
#define SHIFT_W 4
#define SHIFT_Q 3

enum class Bit
{
    Bit0,
    Bit1,
    Bit2,
    Bit3,
    Bit4,
    Bit5,
    Bit6,
    Bit7,
};

class GBInstructionContext
{
private:
    bool m_Bits[BYTE_SIZE];
    quint8 m_x;
    quint8 m_y;
    quint8 m_z;
    quint8 m_w;
    quint8 m_q;
    quint16 m_Data;
    quint8 m_Step;
public:
    GBInstructionContext(quint8 opcode);
    quint8 GetX() { return m_x; }
    quint8 GetY() { return m_y; }
    quint8 GetZ() { return m_z; }
    quint8 GetW() { return m_w; }
    quint8 GetQ() { return m_q; }
    bool GetBit(Bit bit) { return m_Bits[*bit]; }
    void SetLSB(quint8 value);
    void SetMSB(quint8 value);
    quint16 Get16BitData() { return m_Data; }
    quint8 Get8BitData() { return m_Data & 0x00FF; }
    quint8 GetStep() { return m_Step; }
    void AdvanceStep() { m_Step++; }
};

#endif // GBINSTRUCTIONCONTEXT_H
