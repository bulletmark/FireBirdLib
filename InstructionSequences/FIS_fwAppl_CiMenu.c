#include "../libFireBird.h"

inline dword FIS_fwAppl_CiMenu(void)
{
  static dword          _Appl_CiMenu = 0;

  if (!_Appl_CiMenu)
    _Appl_CiMenu = TryResolve("_Z11Appl_CiMenu10TYPE_OsdOp");

  return _Appl_CiMenu;
}
