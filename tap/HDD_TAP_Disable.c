#include "FBLib_tap.h"

bool HDD_TAP_Disable(dword TAPID, bool DisableEvents)
{
  TRACEENTER();

  int                   TAPIndex;
  dword                 isDisabled;
  tTMSTAPTaskTable     *TMSTAPTaskTable;

  TAPIndex = HDD_TAP_GetIndexByID(TAPID);
  if(TAPIndex == -1)
  {
    TRACEEXIT();
    return FALSE;
  }

  //The curTapTask variable is not thread safe. Call InitTAPex() if this function will be called from a sub thread
  if(TAP_TableIndex == 0xffffffff)
  {
    dword                *curTapTask;

    curTapTask = (dword*)FIS_vCurTapTask();
    if(!curTapTask)
    {
      TRACEEXIT();
      return FALSE;
    }
    TAP_TableIndex = *curTapTask;
  }

  //Don't disable ourself
  if((dword)TAPIndex == TAP_TableIndex)
  {
    TRACEEXIT();
    return FALSE;
  }

  //The TAP has already the requested state
  isDisabled = HDD_TAP_isDisabled(TAPID);
  if((isDisabled == 1) == DisableEvents)
  {
    TRACEEXIT();
    return FALSE;
  }

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();
  if(!TMSTAPTaskTable)
  {
    TRACEEXIT();
    return FALSE;
  }

  //The TAP will terminate soon
  if(TMSTAPTaskTable[TAPIndex].Status != 1)
  {
    TRACEEXIT();
    return FALSE;
  }

  //Abuse tTMSTAPTaskTable.unused5 as temporary storage for the event handler address
  if(DisableEvents)
  {
    TMSTAPTaskTable[TAPIndex].unused5 = TMSTAPTaskTable[TAPIndex].TAP_EventHandler;
    TMSTAPTaskTable[TAPIndex].TAP_EventHandler = (dword)&HDD_TAP_DisabledEventHandler;
  }
  else
  {
    TMSTAPTaskTable[TAPIndex].TAP_EventHandler = TMSTAPTaskTable[TAPIndex].unused5;
    TMSTAPTaskTable[TAPIndex].unused5 = 0;
  }

  TRACEEXIT();
  return TRUE;
}
