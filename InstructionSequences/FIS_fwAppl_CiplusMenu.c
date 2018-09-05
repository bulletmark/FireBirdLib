#include "libFireBird.h"

inline dword FIS_fwAppl_CiplusMenu(void)
{
  TRACEENTER;

  static dword          _Appl_CiplusMenu = 0;

  if(!_Appl_CiplusMenu)
    _Appl_CiplusMenu = TryResolve("_Z15Appl_CiplusMenu10TYPE_OsdOp");

  TRACEEXIT;
  return _Appl_CiplusMenu;
}
