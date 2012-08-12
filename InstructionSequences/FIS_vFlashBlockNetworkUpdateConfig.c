#include "../libFireBird.h"

inline dword FIS_vFlashBlockNetworkUpdateConfig(void)
{
  static dword          *vFlashNetworkUpdateConfig = 0;

  if(!vFlashNetworkUpdateConfig)
  {
    vFlashNetworkUpdateConfig = (dword*)TryResolve("_networkUpdateConfig");
    if(!vFlashNetworkUpdateConfig) return 0;
  }

  return *vFlashNetworkUpdateConfig;
}
