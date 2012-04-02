#include "../libFireBird.h"

inline dword FIS_vFlashBlockSatInfo(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_satInfo");
    if(!vFlash) return 0;
  }

  return *vFlash;
}

