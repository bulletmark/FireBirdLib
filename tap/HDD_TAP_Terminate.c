#include "FBLib_tap.h"

void HDD_TAP_Terminate(dword TAPID)
{
  TRACEENTER();

  int                   TAPIndex;
  tTMSTAPTaskTable     *TMSTAPTaskTable;

  //Return if that ID is not in use
  TAPIndex = HDD_TAP_GetIndexByID(TAPID);
  if(TAPIndex < 0)
  {
    TRACEEXIT();
    return;
  }

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();
  if(!TMSTAPTaskTable)
  {
    TRACEEXIT();
    return;
  }

  //Be nice and send a stop event to the target TAP
  HDD_TAP_SendEvent(TAPID, FALSE, EVT_STOP, 1, 0);

  TMSTAPTaskTable[TAPIndex].Status = 2;

  TRACEEXIT();
}
