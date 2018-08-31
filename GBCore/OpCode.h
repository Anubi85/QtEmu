#ifndef OPCODE_H
#define OPCODE_H

#include <QtCore>

/* OpCode bits
 * +-+-+-+-+-+-+-+-+
 * |7|6|5|4|3|2|1|0|
 * +-+-+-+-+-+-+-+-+
 * |x|x|y|y|y|z|z|z|
 * +-+-+-+-+-+-+-+-+
 * | | |w|w|f| | | |
 * +-+-+-+-+-+-+-+-+
*/

#define MASK_X 0xC0
#define MASK_Y 0x38
#define MASK_Z 0x07
#define MASK_W 0x30
#define MASK_F 0x08

#define SHIFT_X 6
#define SHIFT_Y 3
#define SHIFT_W 4

class OpCode
{
private:
    quint8 m_x;
    quint8 m_y;
    quint8 m_z;
    quint8 m_w;
    bool m_f;
public:
    OpCode(quint8 value);
    quint8 GetX() { return m_x; }
    quint8 GetY() { return m_y; }
    quint8 GetZ() { return m_z; }
    quint8 GetW() { return m_w; }
    bool GetF() { return m_f; }
};

#endif // OPCODE_H
