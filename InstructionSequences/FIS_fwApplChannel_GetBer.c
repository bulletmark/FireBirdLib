#include "libFireBird.h"

inline dword FIS_fwApplChannel_GetBer(void)
{
  TRACEENTER;

  static dword          _ApplChannel_GetBer = 0;

  if(!_ApplChannel_GetBer)
    _ApplChannel_GetBer = TryResolve("_Z18ApplChannel_GetBerhPh");

  TRACEEXIT;
  return _ApplChannel_GetBer;
}
