#include "libFireBird.h"

inline dword FIS_fwAppl_GetSameTimeEvent(void)
{
  static dword          _Appl_GetSameTimeEvent = 0;

  TRACEENTER();

  if(!_Appl_GetSameTimeEvent)
    _Appl_GetSameTimeEvent = TryResolve("_Z21Appl_GetSameTimeEventhttt");

  TRACEEXIT();
  return _Appl_GetSameTimeEvent;
}
