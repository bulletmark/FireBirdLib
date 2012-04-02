#include "../libFireBird.h"

inline dword FIS_fwAppl_SetProviderName(void)
{
  static dword          _Appl_SetProviderName = 0;

  if (!_Appl_SetProviderName)
    _Appl_SetProviderName = TryResolve("_Z20Appl_SetProviderNamePc");

  return _Appl_SetProviderName;
}
