#include "FBLib_tap.h"

bool HDD_TAP_isDisabledAll(void)
{
  TRACEENTER();

  dword                 i;
  tTMSTAPTaskTable     *TMSTAPTaskTable;

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();

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

  for(i = 0; i < TAP_MAX; i++)
  {
    if((i != TAP_TableIndex) && (TMSTAPTaskTable[i].Status == 1) && (TMSTAPTaskTable[i].unused5 == 0))
    {
      TRACEEXIT();
      return FALSE;
    }
  }

  TRACEEXIT();
  return TRUE;
}
