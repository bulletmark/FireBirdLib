#include "FBLib_main.h"
#include "../libFireBird.h"

const char              *__fblib_version__ = "__FBLIB_VERSION_TMS__ " __FBLIB_VERSION__;

word                    ApplID;
dword                   TAP_TableIndex;
bool                    LibInitialized = FALSE;

bool InitTAPex()
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("InitTAPex");
  #endif

  if(LibInitialized)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return TRUE;
  }

  ApplID = TAP_GetVersion();

  dword *pcurTapTask = (dword*)FIS_vCurTapTask();
  if(pcurTapTask) TAP_TableIndex = *pcurTapTask;

  #ifdef DEBUG_FIREBIRDLIB
    TAP_Print("FireBirdLib: SystemID=%d, Appl=%4.4x\n", GetSysID(), ApplID);
  #endif

  LibInitialized = TRUE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return LibInitialized;
}
