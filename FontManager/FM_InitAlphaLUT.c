#include                "FBLib_FontManager.h"

tAlphaLUT  AlphaLUT[256];

void FM_InitAlphaLUT(dword fgColor, dword bgColor, float AntiAliasFactor)
{
  TRACEENTER;

  int                   i;
  dword                 x;

  for(i = 0; i < 255; i++)
  {
    x = FM_AlphaBlend(i, (fgColor >> 16) & 0xff, (bgColor >> 16) & 0xff, AntiAliasFactor);
    AlphaLUT[i].r = (x > 255) ? 255 : x;

    x = FM_AlphaBlend(i, (fgColor >>  8) & 0xff, (bgColor >>  8) & 0xff, AntiAliasFactor);
    AlphaLUT[i].g = (x > 255) ? 255 : x;

    x = FM_AlphaBlend(i,  fgColor        & 0xff,  bgColor        & 0xff, AntiAliasFactor);
    AlphaLUT[i].b = (x > 255) ? 255 : x;
  }

  TRACEEXIT;
}
