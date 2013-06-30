#include "../libFireBird.h"

inline dword FIS_fwAppl_WaitEvt(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_WaitEvt");
  #endif

  static dword          _Appl_WaitEvt = 0;

  if(!_Appl_WaitEvt)
    _Appl_WaitEvt = TryResolve("_Z12Appl_WaitEvtjPjjjj");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_WaitEvt;
}
