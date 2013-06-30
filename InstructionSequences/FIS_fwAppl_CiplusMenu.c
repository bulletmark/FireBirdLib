#include "../libFireBird.h"

inline dword FIS_fwAppl_CiplusMenu(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_CiplusMenu");
  #endif

  static dword          _Appl_CiplusMenu = 0;

  if(!_Appl_CiplusMenu)
    _Appl_CiplusMenu = TryResolve("_Z15Appl_CiplusMenu10TYPE_OsdOp");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_CiplusMenu;
}
