#include "FBLib_ini.h"
#include "libFireBird.h"

void INISetRGB8(char *Key, byte Red, byte Green, byte Blue)
{
  TRACEENTER();

  char rgb[12];

  sprintf(rgb, "%3.3d,%3.3d,%3.3d", Red, Green, Blue);
  INISetString(Key, rgb);

  TRACEEXIT();
}
