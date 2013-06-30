#include "../libFireBird.h"

inline dword FIS_fwAppl_EvtProc_PincodeKey(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_EvtProc_PincodeKey");
  #endif

  static dword          _Appl_EvtProc_PincodeKey = 0;

  if(!_Appl_EvtProc_PincodeKey)
    _Appl_EvtProc_PincodeKey = TryResolve("_Z23Appl_EvtProc_PincodeKeyjj");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_EvtProc_PincodeKey;
}
