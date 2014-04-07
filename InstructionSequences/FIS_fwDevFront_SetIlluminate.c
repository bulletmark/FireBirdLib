#include "../libFireBird.h"

inline dword FIS_fwDevFront_SetIlluminate(void)
{
  TRACEENTER();

  static dword          _DevFront_SetIlluminate = 0;

  if(!_DevFront_SetIlluminate)
    _DevFront_SetIlluminate = TryResolve("DevFront_SetIlluminate");

  TRACEEXIT();
  return _DevFront_SetIlluminate;
}
