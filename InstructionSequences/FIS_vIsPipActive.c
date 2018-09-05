#include "libFireBird.h"

inline dword FIS_vIsPipActive(void)
{
  TRACEENTER;

  static dword          _isPipActive = 0;

  if(!_isPipActive)
    _isPipActive = TryResolve("_isPipActive");

  TRACEEXIT;
  return _isPipActive;
}
