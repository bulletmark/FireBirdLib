#include "../libFireBird.h"

inline dword FIS_fwAppl_GetIsExternal(void)
{
  TRACEENTER();

  static dword          _Appl_GetIsExternal = 0;

  if(!_Appl_GetIsExternal)
    _Appl_GetIsExternal = TryResolve("_Z18Appl_GetIsExternalv");

  TRACEEXIT();
  return _Appl_GetIsExternal;
}
