#include "../libFireBird.h"

inline dword FIS_fwAppl_SetProviderName(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_SetProviderName");
  #endif

  static dword          _Appl_SetProviderName = 0;

  if(!_Appl_SetProviderName)
    _Appl_SetProviderName = TryResolve("_Z20Appl_SetProviderNamePc");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_SetProviderName;
}
