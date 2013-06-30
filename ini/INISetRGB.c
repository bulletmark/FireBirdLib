#include "FBLib_ini.h"
#include "../libFireBird.h"

void INISetRGB(char *Key, byte Red, byte Green, byte Blue)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INISetRGB");
  #endif

  char rgb[10];

  sprintf(rgb, "%2.2d,%2.2d,%2.2d", Red & 0x1f, Green & 0x1f, Blue & 0x1f);
  INISetString(Key, rgb);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
