#include "../libFireBird.h"

inline dword FIS_fwAppl_ClrTimer(void)
{
  static dword          _Appl_ClrTimer = 0;

  if (!_Appl_ClrTimer)
    _Appl_ClrTimer = TryResolve("_Z13Appl_ClrTimerRh");

  return _Appl_ClrTimer;
}
