#include "../libFireBird.h"

inline dword FIS_fwAppl_SetIsExternal(void)
{
  static dword          _Appl_SetIsExternal = 0;

  if (!_Appl_SetIsExternal)
    _Appl_SetIsExternal = TryResolve("_Z18Appl_SetIsExternalb");

  return _Appl_SetIsExternal;
}
