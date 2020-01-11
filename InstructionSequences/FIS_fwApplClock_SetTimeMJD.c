#include "libFireBird.h"

inline dword FIS_fwApplClock_SetTimeMJD(void)
{
  TRACEENTER();

  static dword          _ApplClock_SetTimeMJD = 0;

  if(!_ApplClock_SetTimeMJD)
    _ApplClock_SetTimeMJD = TryResolve("_Z20ApplClock_SetTimeMJDthhh");

  TRACEEXIT();
  return _ApplClock_SetTimeMJD;
}
