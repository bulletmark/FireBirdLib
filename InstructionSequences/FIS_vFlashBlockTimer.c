#include "../libFireBird.h"

inline dword FIS_vFlashBlockTimer(void)
{
  static dword          *vFlashTimer = 0;

  if(!vFlashTimer)
  {
    vFlashTimer = (dword*)TryResolve("_timer");
    if(!vFlashTimer) return 0;
  }

  return *vFlashTimer;
}
