#include "FBLib_ini.h"
#include "../libFireBird.h"

void INISetHexDWord(char *Key, dword Value)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INISetHexDWord");
  #endif

  char                  s[10];

  sprintf(s, "%08x", Value);
  INISetString(Key, s);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
