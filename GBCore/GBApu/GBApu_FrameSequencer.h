#ifndef GBAPU_FRAMESEQUENCER_H
#define GBAPU_FRAMESEQUENCER_H

#include <QtGlobal>

class GBApu_FrameSequencer
{
private:
	/*
	 * tttccccccccccccc
	 * c = counter bits (13), produces a 512 Hz sequenser tick
	 * t = tick bits (3), max 8 tick, after that it will reset to zero
	*/
	quint16 m_TickCounter;
public:
	GBApu_FrameSequencer(){ m_TickCounter = 0; }
	~GBApu_FrameSequencer();
	void Tick() { m_TickCounter++; }
	bool IsLengthCounterTick() { return (m_TickCounter & 0x3FFF) == 0; } // even sequencer tick
	bool IsVolumeEnvelopeTick() { return m_TickCounter == 0xE000; } // sequencer tick 8
	bool IsFrequencySweepTick() { return (m_TickCounter & 0x7FFF) == 0x4000; } // sequencer tick 2 and 6
	void Reset(){ m_TickCounter &= 0x1FFF; }
};

#endif // GBAPU_FRAMESEQUENCER_H
