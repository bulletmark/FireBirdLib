#include "FBLib_tap.h"

bool HDD_TAP_isAnyRunning(void)
{
  dword                 i;
  tTMSTAPTaskTable     *TMSTAPTaskTable;

  if (!LibInitialized) InitTAPex ();
  if (!LibInitialized) return FALSE;

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();
  if(!TMSTAPTaskTable) return FALSE;

  for (i = 0; i < TAP_MAX; i++)
  {
    if ((TMSTAPTaskTable[i].Status != 0) && (i != TAP_TableIndex)) return TRUE;
  }

  return FALSE;
}
