#include "../libFireBird.h"

inline dword FIS_vDirectSvcNumTimerId(void)
{
  static dword          _directSvcNumTimerId = 0;

  if(!_directSvcNumTimerId) _directSvcNumTimerId = TryResolve("_directSvcNumTimerId");

  return _directSvcNumTimerId;
}
