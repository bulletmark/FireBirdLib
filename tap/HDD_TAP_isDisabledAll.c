#include "FBLib_tap.h"

bool HDD_TAP_isDisabledAll(void)
{
  dword                 i;
  tTMSTAPTaskTable     *TMSTAPTaskTable;
  dword                *curTAPTask;

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();
  curTAPTask = (dword*)FIS_vCurTapTask();
  if(!curTAPTask || !TMSTAPTaskTable) return FALSE;

  for(i = 0; i < TAP_MAX; i++)
  {
    if((i != *curTAPTask) && (TMSTAPTaskTable[i].Status == 1) && (TMSTAPTaskTable[i].unknown9 == 0)) return FALSE;
  }

  return TRUE;
}
