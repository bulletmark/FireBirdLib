#include "FBLib_ini.h"
#include "../libFireBird.h"

void INISetHexByte(char *Key, byte Value)
{
  TRACEENTER();

  char                  s[4];

  sprintf(s, "%02x", Value);
  INISetString(Key, s);

  TRACEEXIT();
}
