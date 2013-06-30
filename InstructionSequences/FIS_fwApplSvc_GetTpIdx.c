#include "../libFireBird.h"

inline dword FIS_fwApplSvc_GetTpIdx(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwApplSvc_GetTpIdx");
  #endif

  static dword          fwApplSvc_GetTpIdx = 0;

  if(!fwApplSvc_GetTpIdx)
    fwApplSvc_GetTpIdx = TryResolve("_Z16ApplSvc_GetTpIdxhtt");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwApplSvc_GetTpIdx;
}
