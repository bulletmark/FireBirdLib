#include "../libFireBird.h"

inline dword FIS_fwAppl_EnterNormal(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_EnterNormal");
  #endif

  static dword          _Appl_EnterNormal = 0;

  if(!_Appl_EnterNormal)
    _Appl_EnterNormal = TryResolve("_Z16Appl_EnterNormalh");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_EnterNormal;
}
