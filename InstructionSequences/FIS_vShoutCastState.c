#include "../libFireBird.h"

inline dword FIS_vShoutCastState(void)
{
  static dword          _shoutCastState = 0;

  if (!_shoutCastState)
    _shoutCastState = TryResolve("_shoutCastState");

  return _shoutCastState;
}
