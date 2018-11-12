#include "GBAudioModule_NoiseWaveGenerator.h"

bool GBAudioModule_NoiseWaveGenerator::s_LFSRNewBitCalculator[LFSR_NEW_BIT_RES_NUM] =
{ false, true, true, false };
