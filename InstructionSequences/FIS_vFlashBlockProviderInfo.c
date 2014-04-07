#include "../libFireBird.h"

inline dword FIS_vFlashBlockProviderInfo(void)
{
  TRACEENTER();

  static dword          *vFlashProviderInfo = 0;

  if(!vFlashProviderInfo)
    vFlashProviderInfo = (dword*)TryResolve("_providerInfo");

  TRACEEXIT();
  return (vFlashProviderInfo ? *vFlashProviderInfo : 0);
}

