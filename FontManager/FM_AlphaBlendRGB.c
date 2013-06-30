#include                "FBLib_FontManager.h"

dword FM_AlphaBlendRGB(byte Alpha, dword FG, dword BG, float AntiAliasFactor)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FM_AlphaBlendRGB");
  #endif

  dword              red, green, blue;

  red = FM_AlphaBlend(Alpha, (FG >> 16) & 0xff, (BG >> 16) & 0xff, AntiAliasFactor);
  green = FM_AlphaBlend(Alpha, (FG >> 8) & 0xff, (BG >> 8) & 0xff, AntiAliasFactor);
  blue = FM_AlphaBlend(Alpha, FG & 0xff, BG & 0xff, AntiAliasFactor);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ARGB(0, red, green, blue);
}
