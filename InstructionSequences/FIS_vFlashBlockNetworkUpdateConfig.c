#include "../libFireBird.h"

inline dword FIS_vFlashBlockNetworkUpdateConfig(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_networkUpdateConfig");
    if(!vFlash) return 0;
  }

  return *vFlash;
}
