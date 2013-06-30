#include "../libFireBird.h"

inline dword FIS_fwAppl_CiMenu(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_CiMenu");
  #endif

  static dword          _Appl_CiMenu = 0;

  if(!_Appl_CiMenu)
    _Appl_CiMenu = TryResolve("_Z11Appl_CiMenu10TYPE_OsdOp");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_CiMenu;
}
