#include "FBLib_tap.h"

bool HDD_TAP_isRunning (dword TAPID)
{
  return (HDD_TAP_GetIndexByID (TAPID) >= 0);
}
