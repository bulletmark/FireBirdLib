#include "libFireBird.h"

inline dword FIS_vShoutCastState(void)
{
  TRACEENTER();

  static dword          _shoutCastState = 0;

  if(!_shoutCastState)
    _shoutCastState = TryResolve("_shoutCastState");

  TRACEEXIT();
  return _shoutCastState;
}
