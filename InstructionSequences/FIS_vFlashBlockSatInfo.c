#include "libFireBird.h"

inline dword FIS_vFlashBlockSatInfo(void)
{
  TRACEENTER();

  static dword          *vFlashSatInfo = 0;

  if(!vFlashSatInfo)
    vFlashSatInfo = (dword*)TryResolve("_satInfo");

  TRACEEXIT();
  return (vFlashSatInfo ? *vFlashSatInfo : 0);
}
