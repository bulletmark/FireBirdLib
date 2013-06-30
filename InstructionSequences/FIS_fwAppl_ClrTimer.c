#include "../libFireBird.h"

inline dword FIS_fwAppl_ClrTimer(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_ClrTimer");
  #endif

  static dword          _Appl_ClrTimer = 0;

  if(!_Appl_ClrTimer)
    _Appl_ClrTimer = TryResolve("_Z13Appl_ClrTimerRh");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_ClrTimer;
}
