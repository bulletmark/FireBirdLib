#include "FBLib_tap.h"

dword HDD_TAP_SendEvent(dword TAPID, bool AllowParamInterception, word event, dword param1, dword param2)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_SendEvent");
  #endif

  dword                *curTapTask;
  dword                 OrigCurTapTask;
  tTMSTAPTaskTable     *TMSTAPTaskTable;
  dword                 Ret = 0, i;

  dword (*TAPEventHandler)(word Event, dword Param1, dword Param2) = NULL;

  curTapTask = (dword*)FIS_vCurTapTask();
  if(!curTapTask)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  TMSTAPTaskTable = (tTMSTAPTaskTable*)FIS_vTAPTable();
  if(!TMSTAPTaskTable)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  if(TAPID)
  {
    int Index = HDD_TAP_GetIndexByID(TAPID);

    if(Index < 0 || Index >= TAP_MAX)
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return 0;
    }

    TAPEventHandler = (void*)TMSTAPTaskTable[Index].TAP_EventHandler;
    OrigCurTapTask = *curTapTask;
    *curTapTask = Index;
    Ret = TAPEventHandler(event, param1, param2);
    *curTapTask = OrigCurTapTask;
    if((Ret == 0) && AllowParamInterception)
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return 0;
    }
  }
  else
  {
    for(i = 0 ; i < TAP_MAX; ++i)
    {
      TAPEventHandler = (void*)TMSTAPTaskTable[i].TAP_EventHandler;
      if(TAPEventHandler)
      {
        OrigCurTapTask = *curTapTask;
        *curTapTask = i;
        Ret = TAPEventHandler(event, param1, param2);
        *curTapTask = OrigCurTapTask;

        // Zero return value should mean don't pass the value on to other TAPs
        // In this case we don't even call the remaining TAPs
        if((Ret == 0) && AllowParamInterception)
        {
          #ifdef DEBUG_FIREBIRDLIB
            CallTraceExit(NULL);
          #endif

          return 0;
        }
      }
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return Ret;
}
