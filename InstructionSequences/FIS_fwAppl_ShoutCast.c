#include "../libFireBird.h"

inline dword FIS_fwAppl_ShoutCast(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_ShoutCast");
  #endif

  static dword          _Appl_ShoutCast = 0;

  if(!_Appl_ShoutCast)
    _Appl_ShoutCast = TryResolve("_Z14Appl_ShoutCast10TYPE_OsdOp");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_ShoutCast;
}
