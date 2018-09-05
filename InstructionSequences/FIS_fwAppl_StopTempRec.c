#include "libFireBird.h"

inline dword FIS_fwAppl_StopTempRec(void)
{
  TRACEENTER;

  static dword          _Appl_StopTempRec = 0;

  if(!_Appl_StopTempRec)
    _Appl_StopTempRec = TryResolve("_Z16Appl_StopTempRecbb");

  TRACEEXIT;
  return _Appl_StopTempRec;
}
