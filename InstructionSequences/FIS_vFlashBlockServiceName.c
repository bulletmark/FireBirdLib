#include "../libFireBird.h"

inline dword FIS_vFlashBlockServiceName(void)
{
  static dword          *vFlashSvcName = 0;

  if(!vFlashSvcName)
  {
    vFlashSvcName = (dword*)TryResolve("_svcName");
    if(!vFlashSvcName) return 0;
  }

  return *vFlashSvcName;
}

