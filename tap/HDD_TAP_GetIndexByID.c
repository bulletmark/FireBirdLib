#include "FBLib_tap.h"

// Return codes: 0..15 = Position in the TAP table
//                  -1 = TAPID not found
//
int HDD_TAP_GetIndexByID(dword TAPID)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_GetIndexByID");
  #endif

  int                   i;

  for(i = 0; i < TAP_MAX; i++)
    if(HDD_TAP_GetIDByIndex(i) == TAPID)
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return i;
    }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return -1;
}
