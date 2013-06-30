#include "../libFireBird.h"

inline dword FIS_fwApplSvc_GetSvcIdx(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplSvc_GetSvcIdx");
  #endif

  static dword          fwApplSvc_GetSvcIdx = 0;

  if(!fwApplSvc_GetSvcIdx)
    fwApplSvc_GetSvcIdx = TryResolve("_Z17ApplSvc_GetSvcIdxhhtttt");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwApplSvc_GetSvcIdx;
}
