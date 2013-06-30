#include "../libFireBird.h"

inline dword FIS_vFlashBlockProviderInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockProviderInfo");
  #endif

  static dword          *vFlashProviderInfo = 0;

  if(!vFlashProviderInfo)
    vFlashProviderInfo = (dword*)TryResolve("_providerInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashProviderInfo ? *vFlashProviderInfo : 0);
}

