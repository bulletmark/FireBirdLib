#include "../libFireBird.h"

inline dword FIS_fwDevFront_SetIlluminate(void)
{
  static dword          _DevFront_SetIlluminate = 0;

  if (!_DevFront_SetIlluminate)
    _DevFront_SetIlluminate = TryResolve("DevFront_SetIlluminate");

  return _DevFront_SetIlluminate;
}
