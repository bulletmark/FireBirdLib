#include "../libFireBird.h"

inline dword FIS_vFlashBlockTimeInfo(void)
{
  static dword          *vFlashTimeInfo = 0;

  if(!vFlashTimeInfo)
  {
    vFlashTimeInfo = (dword*)TryResolve("_timeInfo");
    if(!vFlashTimeInfo) return 0;
  }

  return *vFlashTimeInfo;
}
