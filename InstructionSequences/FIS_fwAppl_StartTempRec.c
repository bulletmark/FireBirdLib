#include "../libFireBird.h"

inline dword FIS_fwAppl_StartTempRec(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_StartTempRec");
  #endif

  static dword          _Appl_StartTempRec = 0;

  if(!_Appl_StartTempRec)
    _Appl_StartTempRec = TryResolve("_Z17Appl_StartTempRecb");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_StartTempRec;
}
