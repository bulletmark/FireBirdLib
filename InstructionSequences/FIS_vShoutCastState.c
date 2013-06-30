#include "../libFireBird.h"

inline dword FIS_vShoutCastState(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vShoutCastState");
  #endif

  static dword          _shoutCastState = 0;

  if(!_shoutCastState)
    _shoutCastState = TryResolve("_shoutCastState");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _shoutCastState;
}
