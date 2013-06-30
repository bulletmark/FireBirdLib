#include "FBLib_ini.h"
#include "../libFireBird.h"

void INISetARGB8(char *Key, byte Alpha, byte Red, byte Green, byte Blue)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INISetARGB8");
  #endif

  char argb[20];

  sprintf(argb, "%3.3d,%3.3d,%3.3d,%3.3d", Alpha, Red, Green, Blue);
  INISetString(Key, argb);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
