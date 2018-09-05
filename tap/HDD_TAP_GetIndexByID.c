#include "FBLib_tap.h"

// Return codes: 0..15 = Position in the TAP table
//                  -1 = TAPID not found
//
int HDD_TAP_GetIndexByID(dword TAPID)
{
  TRACEENTER;

  int                   i;

  for(i = 0; i < TAP_MAX; i++)
    if(HDD_TAP_GetIDByIndex(i) == TAPID)
    {
      TRACEEXIT;
      return i;
    }

  TRACEEXIT;
  return -1;
}
