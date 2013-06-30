#include "../libFireBird.h"

inline dword FIS_fwAppl_GetIsExternal(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_GetIsExternal");
  #endif

  static dword          _Appl_GetIsExternal = 0;

  if(!_Appl_GetIsExternal)
    _Appl_GetIsExternal = TryResolve("_Z18Appl_GetIsExternalv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_GetIsExternal;
}
