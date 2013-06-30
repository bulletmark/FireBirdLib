#include "FBLib_ini.h"
#include "../libFireBird.h"

void INISetRGB8(char *Key, byte Red, byte Green, byte Blue)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INISetRGB8");
  #endif

  char rgb[12];

  sprintf(rgb, "%3.3d,%3.3d,%3.3d", Red, Green, Blue);
  INISetString(Key, rgb);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
