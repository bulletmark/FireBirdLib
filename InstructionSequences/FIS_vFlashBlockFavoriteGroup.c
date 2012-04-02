#include "../libFireBird.h"

inline dword FIS_vFlashBlockFavoriteGroup(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_favGrp");
    if(!vFlash) return 0;
  }

  return *vFlash;
}

