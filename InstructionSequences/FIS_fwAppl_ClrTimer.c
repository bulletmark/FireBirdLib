#include "libFireBird.h"

inline dword FIS_fwAppl_ClrTimer(void)
{
  TRACEENTER();

  static dword          _Appl_ClrTimer = 0;

  if(!_Appl_ClrTimer)
    _Appl_ClrTimer = TryResolve("_Z13Appl_ClrTimerRh");

  TRACEEXIT();
  return _Appl_ClrTimer;
}
