#include                "FBLib_FontManager.h"

byte FM_AlphaBlend(byte Alpha, byte FG, byte BG, float AntiAliasFactor)
{
  TRACEENTER();

  dword                  Color;
  float                  ColorFactor;

  if(Alpha == 0)
  {
    TRACEEXIT();
    return BG;
  }

  if(Alpha == 0xff)
  {
    TRACEEXIT();
    return FG;
  }

  ColorFactor = (float)((((dword)Alpha * FG) + ((dword)(255 - Alpha) * BG)) >> 8) * AntiAliasFactor;
  Color = (int)ColorFactor;

  TRACEEXIT();
  return (Color > 255) ? 255 : Color;
}
