#include "FBLib_tap.h"

bool HDD_TAP_isDisabledAll(void)
{
  TRACEENTER();

  dword                 i;
  tTMSTAPTaskTable     *TMSTAPTaskTable;
  dword                *curTAPTask;

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();
  curTAPTask = (dword*)FIS_vCurTapTask();
  if(!curTAPTask || !TMSTAPTaskTable)
  {
    TRACEEXIT();
    return FALSE;
  }

  for(i = 0; i < TAP_MAX; i++)
  {
    if((i != *curTAPTask) && (TMSTAPTaskTable[i].Status == 1) && (TMSTAPTaskTable[i].unused5 == 0))
    {
      TRACEEXIT();
      return FALSE;
    }
  }

  TRACEEXIT();
  return TRUE;
}
