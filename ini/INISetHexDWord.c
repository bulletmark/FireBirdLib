#include "FBLib_ini.h"
#include "../libFireBird.h"

void INISetHexDWord(char *Key, dword Value)
{
  TRACEENTER();

  char                  s[10];

  sprintf(s, "%08x", Value);
  INISetString(Key, s);

  TRACEEXIT();
}
