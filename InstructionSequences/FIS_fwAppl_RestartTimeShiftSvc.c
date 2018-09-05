#include "libFireBird.h"

inline dword FIS_fwAppl_RestartTimeShiftSvc(void)
{
  TRACEENTER;

  static dword          _Appl_RestartTimeShiftSvc = 0;

  if(!_Appl_RestartTimeShiftSvc)
    _Appl_RestartTimeShiftSvc = TryResolve("_Z24Appl_RestartTimeShiftSvcbj");

  TRACEEXIT;
  return _Appl_RestartTimeShiftSvc;
}
