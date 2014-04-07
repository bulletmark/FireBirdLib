#include "../libFireBird.h"

inline dword FIS_fwAppl_EvtProc_PincodeKey(void)
{
  TRACEENTER();

  static dword          _Appl_EvtProc_PincodeKey = 0;

  if(!_Appl_EvtProc_PincodeKey)
    _Appl_EvtProc_PincodeKey = TryResolve("_Z23Appl_EvtProc_PincodeKeyjj");

  TRACEEXIT();
  return _Appl_EvtProc_PincodeKey;
}
