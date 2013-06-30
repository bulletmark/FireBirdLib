#include "../libFireBird.h"

inline dword FIS_fwAppl_DeleteRadioSvcName(void)
{
  static dword          _Appl_DeleteRadioSvcName = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_DeleteRadioSvcName");
  #endif

  if(!_Appl_DeleteRadioSvcName)
    _Appl_DeleteRadioSvcName = TryResolve("_Z23Appl_DeleteRadioSvcNametb");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_DeleteRadioSvcName;
}
