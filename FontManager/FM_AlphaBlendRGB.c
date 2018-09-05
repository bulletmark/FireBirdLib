#include                "FBLib_FontManager.h"

dword FM_AlphaBlendRGB(byte Alpha, dword FG, dword BG, float AntiAliasFactor)
{
  TRACEENTER;

  dword              red, green, blue;

  red = FM_AlphaBlend(Alpha, (FG >> 16) & 0xff, (BG >> 16) & 0xff, AntiAliasFactor);
  green = FM_AlphaBlend(Alpha, (FG >> 8) & 0xff, (BG >> 8) & 0xff, AntiAliasFactor);
  blue = FM_AlphaBlend(Alpha, FG & 0xff, BG & 0xff, AntiAliasFactor);

  TRACEEXIT;
  return ARGB(0, red, green, blue);
}
