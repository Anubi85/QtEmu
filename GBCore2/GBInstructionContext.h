#ifndef GBINSTRUCTIONCONTEXT_H
#define GBINSTRUCTIONCONTEXT_H

#include <QtCore>

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

#define MASK_X 0xC0
#define MASK_Y 0x38
#define MASK_Z 0x07
#define MASK_W 0x30
#define MASK_F 0x08
#define MASK_G 0x20
#define MASK_Q 0x18

#define SHIFT_X 6
#define SHIFT_Y 3
#define SHIFT_W 4
#define SHIFT_Q 3

class GBInstructionContext
{
private:
    quint8 m_x;
    quint8 m_y;
    quint8 m_z;
    quint8 m_w;
    bool m_f;
    quint8 m_q;
    bool m_g;
public:
    GBInstructionContext(quint8 opcode);
    quint8 GetX() { return m_x; }
    quint8 GetY() { return m_y; }
    quint8 GetZ() { return m_z; }
    quint8 GetW() { return m_w; }
    bool GetF() { return m_f; }
    quint8 GetQ() { return m_q; }
    bool GetG() { return m_g; }
};

#endif // GBINSTRUCTIONCONTEXT_H
