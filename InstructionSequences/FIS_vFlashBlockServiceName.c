#include "libFireBird.h"

inline dword FIS_vFlashBlockServiceName(void)
{
  TRACEENTER;

  static dword          *vFlashSvcName = 0;

  if(!vFlashSvcName)
    vFlashSvcName = (dword*)TryResolve("_svcName");

  TRACEEXIT;
  return (vFlashSvcName ? *vFlashSvcName : 0);
}

