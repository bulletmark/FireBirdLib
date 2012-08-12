#ifndef FBLIB_FONTMANAGER_H
#define FBLIB_FONTMANAGER_H

#include "../libFireBird.h"

typedef struct
{
  byte  r;
  byte  g;
  byte  b;
} tAlphaLUT;

extern tAlphaLUT  AlphaLUT[256];


bool FM_isValidCharacter(byte Char);
byte FM_CharToIndex(byte Char);
byte FM_AlphaBlend(byte Alpha, byte FG, byte BG, float AntiAliasFactor);
void FM_InitAlphaLUT(dword fgColor, dword bgColor, float AntiAliasFactor);
dword FM_AlphaBlendRGB(byte Alpha, dword FG, dword BG, float AntiAliasFactor);

#endif
