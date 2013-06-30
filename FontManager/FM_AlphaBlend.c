#include                "FBLib_FontManager.h"

byte FM_AlphaBlend(byte Alpha, byte FG, byte BG, float AntiAliasFactor)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FM_AlphaBlend");
  #endif

  dword                  Color;
  float                  ColorFactor;

  if(Alpha == 0)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return BG;
  }

  if(Alpha == 0xff)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FG;
  }

  ColorFactor = (float)((((dword)Alpha * FG) + ((dword)(255 - Alpha) * BG)) >> 8) * AntiAliasFactor;
  Color = (int)ColorFactor;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (Color > 255) ? 255 : Color;
}
