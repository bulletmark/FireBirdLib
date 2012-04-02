#include "../libFireBird.h"

inline dword FIS_vFlashBlockLanIPConfig(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_oldLanIpConfig");
    if(!vFlash) return 0;
  }

  return *vFlash;
}

