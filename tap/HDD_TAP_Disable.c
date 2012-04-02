#include "FBLib_tap.h"

bool HDD_TAP_Disable(dword TAPID, bool DisableEvents)
{
  int                   TAPIndex;
  dword                 isDisabled;
  dword                *curTAPTask;
  tTMSTAPTaskTable     *TMSTAPTaskTable;

  TAPIndex = HDD_TAP_GetIndexByID(TAPID);
  if(TAPIndex == -1) return FALSE;

  //Don't disable ourself
  curTAPTask = (dword*)FIS_vCurTapTask();
  if(!curTAPTask || ((dword)TAPIndex == *curTAPTask)) return FALSE;

  //The TAP has already the requested state
  isDisabled = HDD_TAP_isDisabled (TAPID);
  if((isDisabled == 1) == DisableEvents) return FALSE;

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();
  if(!TMSTAPTaskTable) return FALSE;

  //The TAP will terminate soon
  if(TMSTAPTaskTable[TAPIndex].Status != 1) return FALSE;

  //Abuse tTMSTAPTaskTable.unknown9 as temporary storage for the event handler address
  if (DisableEvents)
  {
    TMSTAPTaskTable[TAPIndex].unknown9 = TMSTAPTaskTable[TAPIndex].TAP_EventHandler;
    TMSTAPTaskTable[TAPIndex].TAP_EventHandler = (dword)&HDD_TAP_DisabledEventHandler;
  }
  else
  {
    TMSTAPTaskTable[TAPIndex].TAP_EventHandler = TMSTAPTaskTable[TAPIndex].unknown9;
    TMSTAPTaskTable[TAPIndex].unknown9 = 0;
  }

  return TRUE;
}
