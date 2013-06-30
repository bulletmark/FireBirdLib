#include "../libFireBird.h"

inline dword FIS_vFlashBlockServiceName(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockServiceName");
  #endif

  static dword          *vFlashSvcName = 0;

  if(!vFlashSvcName)
    vFlashSvcName = (dword*)TryResolve("_svcName");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashSvcName ? *vFlashSvcName : 0);
}

