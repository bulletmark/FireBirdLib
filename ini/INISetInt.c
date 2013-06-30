#include "FBLib_ini.h"
#include "../libFireBird.h"

void INISetInt(char *Key, long int Value)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("INISetInt");
  #endif

  char                  s[12];

  sprintf(s, "%d", Value);
  INISetString(Key, s);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
