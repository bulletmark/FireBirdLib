#include "../libFireBird.h"

inline dword FIS_vDirectSvcNumTimerId(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vDirectSvcNumTimerId");
  #endif

  static dword          _directSvcNumTimerId = 0;

  if(!_directSvcNumTimerId)
    _directSvcNumTimerId = TryResolve("_directSvcNumTimerId");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _directSvcNumTimerId;
}
