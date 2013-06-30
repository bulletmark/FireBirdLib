#include "FBLib_tap.h"

bool HDD_TAP_isRunning(dword TAPID)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_isRunning");
  #endif

  bool ret = (HDD_TAP_GetIndexByID(TAPID) >= 0);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
