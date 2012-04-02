#include "../libFireBird.h"

inline dword FIS_vFlashBlockDLNAData(void)
{
  static dword          *vFlash = 0;

  if(!vFlash)
  {
    vFlash = (dword*)TryResolve("_dlnaData");
    if(!vFlash) return 0;
  }

  return *vFlash;
}

