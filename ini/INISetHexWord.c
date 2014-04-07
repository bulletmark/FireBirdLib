#include "FBLib_ini.h"
#include "../libFireBird.h"

void INISetHexWord(char *Key, word Value)
{
  TRACEENTER();

  char                  s[6];

  sprintf(s, "%04x", Value);
  INISetString(Key, s);

  TRACEEXIT();
}
