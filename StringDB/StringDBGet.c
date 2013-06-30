#include                "../libFireBird.h"

char *StringDBGet(tStringDB *StringDB, dword Index)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringDBGet");
  #endif

  char *ret;

  if(!StringDB)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return '\0';
  }

  ret = StringDB->DB + Index;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
