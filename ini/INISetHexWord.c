#include "FBLib_ini.h"
#include "../libFireBird.h"

void INISetHexWord(char *Key, word Value)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INISetHexWord");
  #endif

  char                  s[6];

  sprintf(s, "%04x", Value);
  INISetString(Key, s);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
