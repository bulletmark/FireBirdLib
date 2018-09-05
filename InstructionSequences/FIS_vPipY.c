#include "libFireBird.h"

inline dword FIS_vPipY(void)
{
  TRACEENTER;

  static dword          _pipY = 0;

  if(!_pipY)
    _pipY = TryResolve("_pipY");

  TRACEEXIT;
  return _pipY;
}
