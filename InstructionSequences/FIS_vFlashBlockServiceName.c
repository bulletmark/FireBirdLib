#include "../libFireBird.h"

inline dword FIS_vFlashBlockServiceName(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_svcName");
    if(!vFlash) return 0;
  }

  return *vFlash;
}

