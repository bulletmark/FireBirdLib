#include "../libFireBird.h"

inline dword FIS_vFlashBlockOTAInfo(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_otaInfo");
    if(!vFlash) return 0;
  }

  return *vFlash;
}

