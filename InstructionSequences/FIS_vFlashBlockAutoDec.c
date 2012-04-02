#include "../libFireBird.h"

inline dword FIS_vFlashBlockAutoDec(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_autoDec");
    if(!vFlash) return 0;
  }

  return *vFlash;
}
