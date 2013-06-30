#include "FBLib_tap.h"

bool HDD_TAP_isAnyRunning(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_isAnyRunning");
  #endif

  dword                 i;
  tTMSTAPTaskTable     *TMSTAPTaskTable;

  if(!LibInitialized) InitTAPex();
  if(!LibInitialized)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();
  if(!TMSTAPTaskTable)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  for(i = 0; i < TAP_MAX; i++)
  {
    if((TMSTAPTaskTable[i].Status != 0) && (i != TAP_TableIndex))
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return TRUE;
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
