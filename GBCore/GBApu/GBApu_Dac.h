#pragma once

#include <QtGlobal>

class GBApu_Dac
{
private:
	bool m_IsEnabled;
	quint8& m_Sample;
public:
    GBApu_Dac(quint8& sample) : m_Sample(sample) { }
    ~GBApu_Dac() { }
	void TurnOn() { m_IsEnabled = true; }
	void TurnOff() { m_IsEnabled = false; }
	bool IsEnabled() { return m_IsEnabled; }
    quint8 GetSample() { return m_IsEnabled ? (m_Sample & 0x0F) : 0.0; }
};
