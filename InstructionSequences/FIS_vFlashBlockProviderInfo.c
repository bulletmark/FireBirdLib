#include "../libFireBird.h"

inline dword FIS_vFlashBlockProviderInfo(void)
{
  static dword          *vFlashProviderInfo = 0;

  if(!vFlashProviderInfo)
  {
    vFlashProviderInfo = (dword*)TryResolve("_providerInfo");
    if(!vFlashProviderInfo) return 0;
  }

  return *vFlashProviderInfo;
}

