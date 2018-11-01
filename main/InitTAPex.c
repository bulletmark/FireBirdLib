#include "FBLib_main.h"
#include "libFireBird.h"

const char              *__fblib_version__ = "__FBLIB_VERSION_TMS__ " __FBLIB_VERSION__;

word                    ApplID;
dword                   TAP_TableIndex = 0xffffffff;
bool                    LibInitialized = FALSE;

bool InitTAPex()
{
  TRACEENTER();

  if(LibInitialized)
  {
    TRACEEXIT();
    return TRUE;
  }

  ApplID = TAP_GetVersion();

  dword *pcurTapTask = (dword*)FIS_vCurTapTask();

  if (pcurTapTask)
  {
    TAP_TableIndex = *pcurTapTask;
    LibInitialized = TRUE;
  }

  TRACEEXIT();
  return LibInitialized;
}
