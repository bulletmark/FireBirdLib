#include "../libFireBird.h"

inline dword FIS_fwAppl_StopTempRec(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_StopTempRec");
  #endif

  static dword          _Appl_StopTempRec = 0;

  if(!_Appl_StopTempRec)
    _Appl_StopTempRec = TryResolve("_Z16Appl_StopTempRecbb");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_StopTempRec;
}
