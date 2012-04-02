#include "../libFireBird.h"

inline dword FIS_vFlashBlockTVServices(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_tvSvc");
    if(!vFlash) return 0;
  }

  return *vFlash;
}
