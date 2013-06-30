#include "FBLib_tap.h"

dword HDD_TAP_Callback(dword TAPID, void *ProcedureAddress, dword param1, dword param2, dword param3, dword param4)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_Callback");
  #endif

  dword                 Ret = 0;
  dword                *curTapTask;
  dword                 OrigCurTapTask;

  dword (*Callback)(dword param1, dword param2, dword param3, dword param4) = NULL;

  if(TAPID)
  {
    curTapTask = (dword*)FIS_vCurTapTask();
    if(!curTapTask)
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return 0;
    }

    int Index = HDD_TAP_GetIndexByID(TAPID);
    if(Index < 0 || Index >= TAP_MAX)
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return 0;
    }

    Callback = ProcedureAddress;
    OrigCurTapTask = *curTapTask;
    *curTapTask = Index;
    Ret = Callback(param1, param2, param3, param4);
    *curTapTask = OrigCurTapTask;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return Ret;
}
