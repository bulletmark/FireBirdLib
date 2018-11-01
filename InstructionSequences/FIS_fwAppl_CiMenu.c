#include "libFireBird.h"

inline dword FIS_fwAppl_CiMenu(void)
{
  TRACEENTER();

  static dword          _Appl_CiMenu = 0;

  if(!_Appl_CiMenu)
    _Appl_CiMenu = TryResolve("_Z11Appl_CiMenu10TYPE_OsdOp");

  TRACEEXIT();
  return _Appl_CiMenu;
}
