#include "../libFireBird.h"

inline dword FIS_fwAppl_GetCurrentEvent(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_GetCurrentEvent");
  #endif

  static dword          _Appl_GetCurrentEvent = 0;

  if(!_Appl_GetCurrentEvent)
    _Appl_GetCurrentEvent = TryResolve("_Z20Appl_GetCurrentEventhttt");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_GetCurrentEvent;
}
