#include "../libFireBird.h"

inline dword FIS_fwAppl_AddSvcName(void)
{
  static dword          _Appl_AddSvcName = 0;

  if (!_Appl_AddSvcName)
    _Appl_AddSvcName = TryResolve("_Z15Appl_AddSvcNamePKc");

  return _Appl_AddSvcName;
}
