#include "FBLib_tap.h"

// Return codes: 0 = not disabled or no TAPID not found
//               1 = The target TAP has been disabled
//               2 = return code not used by the TMS version
//               3 = return code not used by the TMS version
//
dword HDD_TAP_isDisabled(dword TAPID)
{
  tTMSTAPTaskTable     *TMSTAPTaskTable;
  int                   TAPIndex;

  TAPIndex = HDD_TAP_GetIndexByID(TAPID);
  if(TAPIndex == -1) return 0;

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();

  return (TMSTAPTaskTable[TAPIndex].unknown9 ? 1 : 0);
}
