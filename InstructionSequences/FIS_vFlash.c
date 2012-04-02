#include "../libFireBird.h"

inline dword FIS_vFlash(void)
{
  static dword          vFlash = 0;

  if(!vFlash)
  {
    dword *_applFlashAddr = (dword*)TryResolve("_applFlashAddr");

    if(!_applFlashAddr) return 0;
    vFlash = *_applFlashAddr;
  }

  return vFlash;
}
