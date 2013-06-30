#include "../libFireBird.h"

inline dword FIS_fwAppl_SetIsExternal(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_SetIsExternal");
  #endif

  static dword          _Appl_SetIsExternal = 0;

  if(!_Appl_SetIsExternal)
    _Appl_SetIsExternal = TryResolve("_Z18Appl_SetIsExternalb");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_SetIsExternal;
}
