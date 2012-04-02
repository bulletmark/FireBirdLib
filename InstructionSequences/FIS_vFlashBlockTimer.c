#include "../libFireBird.h"

inline dword FIS_vFlashBlockTimer(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_timer");
    if(!vFlash) return 0;
  }

  return *vFlash;
}
