#include "libFireBird.h"

inline dword FIS_fwAppl_DeleteRadioSvcName(void)
{
  static dword          _Appl_DeleteRadioSvcName = 0;

  TRACEENTER();

  if(!_Appl_DeleteRadioSvcName)
    _Appl_DeleteRadioSvcName = TryResolve("_Z23Appl_DeleteRadioSvcNametb");

  TRACEEXIT();
  return _Appl_DeleteRadioSvcName;
}
