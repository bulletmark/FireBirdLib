#include "libFireBird.h"

inline dword FIS_fwApplSvc_GetSvcIdx(void)
{
  TRACEENTER;

  static dword          fwApplSvc_GetSvcIdx = 0;

  if(!fwApplSvc_GetSvcIdx)
    fwApplSvc_GetSvcIdx = TryResolve("_Z17ApplSvc_GetSvcIdxhhtttt");

  TRACEEXIT;
  return fwApplSvc_GetSvcIdx;
}
