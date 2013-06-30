#include "FBLib_tap.h"

// Return codes: 0 = not disabled or no TAPID not found
//               1 = The target TAP has been disabled
//               2 = return code not used by the TMS version
//               3 = return code not used by the TMS version
//
dword HDD_TAP_isDisabled(dword TAPID)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_isDisabled");
  #endif

  tTMSTAPTaskTable     *TMSTAPTaskTable;
  int                   TAPIndex;
  dword                 ret;

  TAPIndex = HDD_TAP_GetIndexByID(TAPID);
  if(TAPIndex == -1)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();
  ret = (TMSTAPTaskTable[TAPIndex].unknown9 ? 1 : 0);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
