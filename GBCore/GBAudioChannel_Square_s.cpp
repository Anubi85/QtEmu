#include "GBAudioChannel_Square.h"

quint8 GBAudioChannel_Square::s_DutyCicleSamples[DUTY_CICLES_NUM][DUTY_CICLES_VALUES_NUM] =
{
    { 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 1, 1, 1 },
    { 0, 1, 1, 1, 1, 1, 1, 0 },
};
