#include "../libFireBird.h"

inline dword FIS_fwAppl_DeleteTvSvcName(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_DeleteTvSvcName");
  #endif

  static dword          _Appl_DeleteTvSvcName = 0;

  if(!_Appl_DeleteTvSvcName)
    _Appl_DeleteTvSvcName = TryResolve("_Z20Appl_DeleteTvSvcNametb");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_DeleteTvSvcName;
}
