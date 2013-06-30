#include                "../libFireBird.h"

bool StringDBDestroy(tStringDB *StringDB)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StringDBDestroy");
  #endif

  if(!StringDB)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(StringDB->DB) TAP_MemFree(StringDB->DB);
  StringDBInit(StringDB, 0);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
