#include "../libFireBird.h"

inline dword FIS_vFlashBlockTransponderInfo(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_tpInfo");
    if(!vFlash) return 0;
  }

  return *vFlash;
}
