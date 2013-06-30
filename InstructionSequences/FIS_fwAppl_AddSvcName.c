#include "../libFireBird.h"

inline dword FIS_fwAppl_AddSvcName(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_AddSvcName");
  #endif

  static dword          _Appl_AddSvcName = 0;

  if(!_Appl_AddSvcName)
    _Appl_AddSvcName = TryResolve("_Z15Appl_AddSvcNamePKc");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_AddSvcName;
}
