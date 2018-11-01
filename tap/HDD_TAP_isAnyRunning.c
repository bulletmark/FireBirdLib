#include "FBLib_tap.h"

bool HDD_TAP_isAnyRunning(void)
{
  TRACEENTER();

  dword                 i;
  tTMSTAPTaskTable     *TMSTAPTaskTable;

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();

  if(!TMSTAPTaskTable || (!LibInitialized && !InitTAPex()))
  {
    TRACEEXIT();
    return FALSE;
  }

  for(i = 0; i < TAP_MAX; i++)
  {
    if((TMSTAPTaskTable[i].Status != 0) && (i != TAP_TableIndex))
    {
      TRACEEXIT();
      return TRUE;
    }
  }

  TRACEEXIT();
  return FALSE;
}
