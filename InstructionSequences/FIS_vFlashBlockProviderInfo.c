#include "../libFireBird.h"

inline dword FIS_vFlashBlockProviderInfo(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_providerInfo");
    if(!vFlash) return 0;
  }

  return *vFlash;
}

