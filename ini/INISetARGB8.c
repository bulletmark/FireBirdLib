#include "FBLib_ini.h"
#include "../libFireBird.h"

void INISetARGB8(char *Key, byte Alpha, byte Red, byte Green, byte Blue)
{
  TRACEENTER();

  char argb[20];

  sprintf(argb, "%3.3d,%3.3d,%3.3d,%3.3d", Alpha, Red, Green, Blue);
  INISetString(Key, argb);

  TRACEEXIT();
}
