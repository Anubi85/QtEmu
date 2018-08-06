#ifndef QTGBCPU_H
#define QTGBCPU_H

#include "IQtGBCPU.h"
#include "IQtGBMemory.h"
#include <functional>

#define INSTRUCTION_NUM 256

typedef std::function<void()> Instruction;

class QtGBCPU : public IQtGBCPU
{
private:
    union
    {
        long long All;
        struct
        {
            uchar F;
            uchar A;
            uchar C;
            uchar B;
            uchar E;
            uchar D;
            uchar L;
            uchar H;
        } Single;
        struct
        {
            ushort AF;
            ushort BC;
            ushort DE;
            ushort HL;
        } Double;
        struct
        {
            bool :1;
            bool :1;
            bool :1;
            bool :1;
            bool C:1;
            bool H:1;
            bool N:1;
            bool Z:1;
        } Flags;
    } m_Registers;
    ushort m_PC;
    ushort m_SP;
    IQtGBMemory* m_Memory;
    Instruction m_Instructions[INSTRUCTION_NUM];
    bool m_ErrorOccurred;

    void NOP() {}       //0x00
    void LD_SP_nn();    //0x31
    void XOR_A();       //0xAF
public:
    QtGBCPU();
    void Reset() override;
    void Exec() override;
    bool HasError() override { return m_ErrorOccurred; }
};

#endif // QTGBCPU_H
