#include "FBLib_main.h"

word GetSysID(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetSysID");
  #endif

  word ret = TAP_GetSystemId();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
