#include "../libFireBird.h"

inline dword FIS_vFlashBlockTimeInfo(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_timeInfo");
    if(!vFlash) return 0;
  }

  return *vFlash;
}
