#include "FBLib_tap.h"

dword HDD_TAP_DisableAll(bool DisableEvents)
{
  TRACEENTER;

  dword                 i, TAPID, count = 0;

  for(i = 0; i < TAP_MAX; i++)
  {
    TAPID = HDD_TAP_GetIDByIndex(i);
    if((TAPID != 0) && (!HDD_TAP_Disable(TAPID, DisableEvents))) count++;
  }

  TRACEEXIT;
  return count;
}
