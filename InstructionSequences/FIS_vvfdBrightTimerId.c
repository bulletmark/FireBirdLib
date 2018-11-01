#include "libFireBird.h"

inline dword FIS_vVfdBrightTimerId(void)
{
  TRACEENTER();

  static dword          _vfdBrightTimerId = 0;

  if(!_vfdBrightTimerId)
    _vfdBrightTimerId = TryResolve("_vfdBrightTimerId");

  TRACEEXIT();
  return _vfdBrightTimerId;
}
