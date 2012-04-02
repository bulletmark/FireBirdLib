#include "../libFireBird.h"

inline dword FIS_vVfdTimerId(void)
{
  static dword          _vfdTimerId = 0;

  if (!_vfdTimerId)
    _vfdTimerId = TryResolve("_vfdTimerId");

  return _vfdTimerId;
}
