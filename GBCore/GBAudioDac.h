#ifndef GBAUDIODAC_H
#define GBAUDIODAC_H

#include <QtGlobal>

class GBAudioDac
{
private:
	const qreal c_Gain;
	const qreal c_Offset;
	quint8* m_Registers;
	bool m_IsWaveChannel;
	bool IsEnabled();
public:
	GBAudioDac(quint8* registers, bool isWaveChannel);
	qreal GetSample(quint8 frequencySample, quint8 waveSample, quint8 lengthSample, quint8 volumeSample);
};

#endif // GBAUDIODAC_H
