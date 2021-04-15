#ifndef GBAUDIOMIXER_H
#define GBAUDIOMIXER_H

#include <QtGlobal>

#define SAMPLES_NUM 4

class GBAudioMixer
{
private:
	quint8* m_Switches;
	quint8* m_Volumes;
	qreal m_RightSample;
	qreal m_LeftSample;
	bool IsChannelEnabled(quint8 mask){ return (*m_Switches & mask) != 0; }
	quint8 GetVolume(bool isRight);
	void ComputeSample(bool isRight, qreal sample1, qreal sample2, qreal sample3, qreal sample4);
public:
	GBAudioMixer(quint8* switches, quint8* volumes);
	void Tick(qreal sample1, qreal sample2, qreal sample3, qreal sample4, quint8 masterVolume);
	qreal GetRigthSample(){ return m_RightSample; }
	qreal GetLeftSample(){ return m_LeftSample; }
};

#endif // GBAUDIOMIXER_H
