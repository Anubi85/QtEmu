#ifndef GBAPU_DAC_H
#define GBAPU_DAC_H

#include <QtGlobal>

class GBApu_Dac
{
private:
	const qreal c_Gain = 2.0 / 15.0;
	const qreal c_Offset = -1.0;

	bool m_IsEnabled;
	quint8& m_Sample;
public:
	GBApu_Dac(quint8& sample) : m_Sample(sample) {}
	~GBApu_Dac() {}
	void TurnOn() { m_IsEnabled = true; }
	void TurnOff() { m_IsEnabled = false; }
	bool IsEnabled() { return m_IsEnabled; }
	qreal GetSample() { return m_IsEnabled ? (m_Sample * c_Gain + c_Offset) : 0.0; }
};

#endif // GBAPU_DAC_H
