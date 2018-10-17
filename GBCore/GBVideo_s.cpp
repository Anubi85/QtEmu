#include "GBVideo.h"

quint32 GBVideo::s_Palettes[PALETTE_NUM][PALETTE_SIZE] =
{
    //Monochrome palette
    {
        0xFFFFFFFF, //Color 0b00 [R:255 G:255 B:255]
        0xFFAAAAAA, //Color 0b01 [R:170 G:170 B:170]
        0xFF555555, //Color 0b10 [R: 85 G: 85 B: 85]
        0xFF000000, //Color 0b11 [R:  0 G:  0 B:  0]
    },
    //Red Light palette
    {
        0xFFFFFFFF, //Color 0b00 [R:255 G:255 B:255]
        0xFFF9B3AC, //Color 0b01 [R:249 G:179 B:172]
        0xFFF3676D, //Color 0b10 [R:243 G:103 B:109]
        0xFFED1B24, //Color 0b11 [R:237 G: 27 B: 36]
    },
    //Red Dark palette
    {
        0xFFED1B24, //Color 0b11 [R:237 G: 27 B: 36]
        0xFF9E1218, //Color 0b01 [R:158 G: 18 B: 24]
        0xFF4F090C, //Color 0b10 [R: 79 G:  9 B: 12]
        0xFF000000, //Color 0b11 [R:  0 G:  0 B:  0]
    },
    //Yellow Light palette
    {
        0xFFFFFFFF, //Color 0b00 [R:255 G:255 B:255]
        0xFFFFEDAF, //Color 0b01 [R:255 G:237 B:175]
        0xFFFFDB5F, //Color 0b10 [R:255 G:219 B: 95]
        0xFFFFC90F, //Color 0b11 [R:255 G:201 B: 15]
    },
    //Yellow Dark palette
    {
        0xFFFFC90F, //Color 0b11 [R:255 G:201 B: 15]
        0xFFAA860A, //Color 0b01 [R:170 G:134 B: 10]
        0xFF554305, //Color 0b10 [R: 85 G: 67 B:  5]
        0xFF000000, //Color 0b11 [R:  0 G:  0 B:  0]
    },
    //Green Light palette
    {
        0xFFFFFFFF, //Color 0b00 [R:255 G:255 B:255]
        0xFFB5E5C3, //Color 0b01 [R:181 G:229 B:195]
        0xFF6BCB87, //Color 0b10 [R:107 G:203 B:135]
        0xFF21B14B, //Color 0b11 [R: 33 G:177 B: 75]
    },
    //Green Dark palette
    {
        0xFF21B14B, //Color 0b11 [R: 33 G:177 B: 75]
        0xFF167632, //Color 0b01 [R: 22 G:118 B: 50]
        0xFF0B3B19, //Color 0b10 [R: 11 G: 59 B: 25]
        0xFF000000, //Color 0b11 [R:  0 G:  0 B:  0]
    },
    //Blue Light palette
    {
        0xFFFFFFFF, //Color 0b00 [R:255 G:255 B:255]
        0xFFAAE0F7, //Color 0b01 [R:170 G:224 B:247]
        0xFF55C1EF, //Color 0b10 [R: 85 G:193 B:239]
        0xFF00A2E7, //Color 0b11 [R:  0 G:162 B:231]
    },
    //Blue Dark palette
    {
        0xFF00A2E7, //Color 0b11 [R:  0 G:162 B:231]
        0xFF006C9A, //Color 0b01 [R:  0 G:108 B:154]
        0xFF00364D, //Color 0b10 [R:  0 G: 54 B: 77]
        0xFF000000, //Color 0b11 [R:  0 G:  0 B:  0]
    },
};
