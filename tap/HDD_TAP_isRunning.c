#include "FBLib_tap.h"

bool HDD_TAP_isRunning(dword TAPID)
{
  TRACEENTER;

  bool ret = (HDD_TAP_GetIndexByID(TAPID) >= 0);

  TRACEEXIT;
  return ret;
}
