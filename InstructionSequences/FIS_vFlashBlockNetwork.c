#include "../libFireBird.h"

inline dword FIS_vFlashBlockNetwork(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_network");
    if(!vFlash) return 0;
  }

  return *vFlash;
}

