#include "../libFireBird.h"

inline dword FIS_vFlashBlockServerData(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_serverData");
    if(!vFlash) return 0;
  }

  return *vFlash;
}

