#include "../libFireBird.h"

inline dword FIS_fwAppl_ShoutCast(void)
{
  static dword          _Appl_ShoutCast = 0;

  if (!_Appl_ShoutCast)
    _Appl_ShoutCast = TryResolve("_Z14Appl_ShoutCast10TYPE_OsdOp");

  return _Appl_ShoutCast;
}
