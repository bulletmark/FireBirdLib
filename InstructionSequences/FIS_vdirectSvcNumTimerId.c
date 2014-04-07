#include "../libFireBird.h"

inline dword FIS_vDirectSvcNumTimerId(void)
{
  TRACEENTER();

  static dword          _directSvcNumTimerId = 0;

  if(!_directSvcNumTimerId)
    _directSvcNumTimerId = TryResolve("_directSvcNumTimerId");

  TRACEEXIT();
  return _directSvcNumTimerId;
}
