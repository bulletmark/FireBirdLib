#include "libFireBird.h"

inline dword FIS_fwAppl_GetCurrentEvent(void)
{
  TRACEENTER();

  static dword          _Appl_GetCurrentEvent = 0;

  if(!_Appl_GetCurrentEvent)
    _Appl_GetCurrentEvent = TryResolve("_Z20Appl_GetCurrentEventhttt");

  TRACEEXIT();
  return _Appl_GetCurrentEvent;
}
