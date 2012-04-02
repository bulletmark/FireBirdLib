#include "../libFireBird.h"

inline dword FIS_fwAppl_GetIsExternal(void)
{
  static dword          _Appl_GetIsExternal = 0;

  if (!_Appl_GetIsExternal)
    _Appl_GetIsExternal = TryResolve("_Z18Appl_GetIsExternalv");

  return _Appl_GetIsExternal;
}
