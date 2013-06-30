#include "FBLib_tap.h"

void HDD_TAP_Terminate(dword TAPID)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_Terminate");
  #endif

  int                   TAPIndex;
  tTMSTAPTaskTable     *TMSTAPTaskTable;

  //Return if that ID is not in use
  TAPIndex = HDD_TAP_GetIndexByID(TAPID);
  if(TAPIndex < 0)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();
  if(!TMSTAPTaskTable)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }

  //Be nice and send a stop event to the target TAP
  HDD_TAP_SendEvent(TAPID, FALSE, EVT_STOP, 1, 0);

  TMSTAPTaskTable[TAPIndex].Status = 2;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
