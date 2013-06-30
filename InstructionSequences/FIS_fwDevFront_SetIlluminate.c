#include "../libFireBird.h"

inline dword FIS_fwDevFront_SetIlluminate(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwDevFront_SetIlluminate");
  #endif

  static dword          _DevFront_SetIlluminate = 0;

  if(!_DevFront_SetIlluminate)
    _DevFront_SetIlluminate = TryResolve("DevFront_SetIlluminate");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _DevFront_SetIlluminate;
}
