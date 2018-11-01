#include "libFireBird.h"

inline dword FIS_fwAppl_AddSvcName(void)
{
  TRACEENTER();

  static dword          _Appl_AddSvcName = 0;

  if(!_Appl_AddSvcName)
    _Appl_AddSvcName = TryResolve("_Z15Appl_AddSvcNamePKc");

  TRACEEXIT();
  return _Appl_AddSvcName;
}
