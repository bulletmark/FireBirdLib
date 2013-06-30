#include "../libFireBird.h"

inline dword FIS_vVfdTimerId(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vVfdTimerId");
  #endif

  static dword          _vfdTimerId = 0;

  if(!_vfdTimerId)
    _vfdTimerId = TryResolve("_vfdTimerId");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _vfdTimerId;
}
