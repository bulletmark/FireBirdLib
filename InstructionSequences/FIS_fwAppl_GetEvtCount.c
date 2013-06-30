#include "../libFireBird.h"

inline dword FIS_fwAppl_GetEvtCount(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_GetEvtCount");
  #endif

  static dword          _Appl_GetEvtCount = 0;

  if(!_Appl_GetEvtCount)
    _Appl_GetEvtCount = TryResolve("_Z16Appl_GetEvtCounthttt");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_GetEvtCount;
}
