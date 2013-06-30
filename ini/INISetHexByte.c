#include "FBLib_ini.h"
#include "../libFireBird.h"

void INISetHexByte(char *Key, byte Value)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INISetHexByte");
  #endif

  char                  s[4];

  sprintf(s, "%02x", Value);
  INISetString(Key, s);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
