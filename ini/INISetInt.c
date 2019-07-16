#include "FBLib_ini.h"
#include "libFireBird.h"

void INISetInt(char *Key, long int Value)
{
  TRACEENTER();

  char                  s[12];

  sprintf(s, "%ld", Value);
  INISetString(Key, s);

  TRACEEXIT();
}
