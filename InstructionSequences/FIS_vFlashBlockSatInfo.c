#include "../libFireBird.h"

inline dword FIS_vFlashBlockSatInfo(void)
{
  static dword          *vFlashSatInfo = 0;

  if(!vFlashSatInfo)
  {
    vFlashSatInfo = (dword*)TryResolve("_satInfo");
    if(!vFlashSatInfo) return 0;
  }

  return *vFlashSatInfo;
}
