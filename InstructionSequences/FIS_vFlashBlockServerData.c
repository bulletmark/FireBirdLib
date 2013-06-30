#include "../libFireBird.h"

inline dword FIS_vFlashBlockServerData(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockServerData");
  #endif

  static dword          *vFlashServerData = 0;

  if(!vFlashServerData)
    vFlashServerData = (dword*)TryResolve("_serverData");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashServerData ? *vFlashServerData : 0);
}

