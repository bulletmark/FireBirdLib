#include "../libFireBird.h"

inline dword FIS_fwAppl_RestartTimeShiftSvc(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_RestartTimeShiftSvc");
  #endif

  static dword          _Appl_RestartTimeShiftSvc = 0;

  if(!_Appl_RestartTimeShiftSvc)
    _Appl_RestartTimeShiftSvc = TryResolve("_Z24Appl_RestartTimeShiftSvcbj");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_RestartTimeShiftSvc;
}
