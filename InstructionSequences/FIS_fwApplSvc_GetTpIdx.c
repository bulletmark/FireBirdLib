#include "libFireBird.h"

inline dword FIS_fwApplSvc_GetTpIdx(void)
{
  TRACEENTER();

  static dword          fwApplSvc_GetTpIdx = 0;

  if(!fwApplSvc_GetTpIdx)
    fwApplSvc_GetTpIdx = TryResolve("_Z16ApplSvc_GetTpIdxhtt");

  TRACEEXIT();
  return fwApplSvc_GetTpIdx;
}
