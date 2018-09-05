#include "libFireBird.h"

inline dword FIS_vVfdTimerId(void)
{
  TRACEENTER;

  static dword          _vfdTimerId = 0;

  if(!_vfdTimerId)
    _vfdTimerId = TryResolve("_vfdTimerId");

  TRACEEXIT;
  return _vfdTimerId;
}
