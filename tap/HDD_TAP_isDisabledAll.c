#include "FBLib_tap.h"

bool HDD_TAP_isDisabledAll(void)
{
  TRACEENTER;

  dword                 i;
  tTMSTAPTaskTable     *TMSTAPTaskTable;

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();

  if(!TMSTAPTaskTable || (!LibInitialized && !InitTAPex()))
  {
    TRACEEXIT;
    return FALSE;
  }

  for(i = 0; i < TAP_MAX; i++)
  {
    if((i != TAP_TableIndex) && (TMSTAPTaskTable[i].Status == 1) && (TMSTAPTaskTable[i].unused5 == 0))
    {
      TRACEEXIT;
      return FALSE;
    }
  }

  TRACEEXIT;
  return TRUE;
}
