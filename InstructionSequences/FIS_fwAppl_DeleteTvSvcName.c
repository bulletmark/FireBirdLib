#include "../libFireBird.h"

inline dword FIS_fwAppl_DeleteTvSvcName(void)
{
  TRACEENTER();

  static dword          _Appl_DeleteTvSvcName = 0;

  if(!_Appl_DeleteTvSvcName)
    _Appl_DeleteTvSvcName = TryResolve("_Z20Appl_DeleteTvSvcNametb");

  TRACEEXIT();
  return _Appl_DeleteTvSvcName;
}
