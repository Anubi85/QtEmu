#include "GBWaveGenerator_Square.h"

GBWaveGenerator_Square::GBWaveGenerator_Square(quint8* registers) :
    IGBWaveGenerator (registers)
{

}

void GBWaveGenerator_Square::Reset()
{
    IGBWaveGenerator::Reset();
    m_SampleIdx = 0;
    m_Enabled = true; //always enabled
}

void GBWaveGenerator_Square::Tick()
{
    if ((GetFrequency() == 0) || (--m_Counter == 0))
    {
        m_Counter = (2048 - GetFrequency()) * 4;
        m_Sample = s_DutyCycles[GetDutyCicle()][m_SampleIdx];
        ++m_SampleIdx &= 0x07;
    }
}
