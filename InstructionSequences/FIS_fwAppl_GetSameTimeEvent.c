#include "../libFireBird.h"

inline dword FIS_fwAppl_GetSameTimeEvent(void)
{
  static dword          _Appl_GetSameTimeEvent = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_GetSameTimeEvent");
  #endif

  if(!_Appl_GetSameTimeEvent)
    _Appl_GetSameTimeEvent = TryResolve("_Z21Appl_GetSameTimeEventhttt");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_GetSameTimeEvent;
}
