#include "GBApu_SquareWaveModule.h"

quint8 GBApu_SquareWaveModule::s_DutyCycles[DUTY_CYCLES_NUM][DUTY_CYCLES_SAMPLES] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 1, 1 },
	{ 0, 1, 1, 1, 1, 1, 1, 0 },
};
