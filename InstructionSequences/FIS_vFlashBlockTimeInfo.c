#include "libFireBird.h"

inline dword FIS_vFlashBlockTimeInfo(void)
{
  TRACEENTER;

  static dword          *vFlashTimeInfo = 0;

  if(!vFlashTimeInfo)
    vFlashTimeInfo = (dword*)TryResolve("_timeInfo");

  TRACEEXIT;
  return (vFlashTimeInfo ? *vFlashTimeInfo : 0);
}
