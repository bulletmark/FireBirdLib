#include "../libFireBird.h"

inline dword FIS_fwAppl_PvrList(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_PvrList");
  #endif

  static dword          _Appl_PvrList = 0;

  if(!_Appl_PvrList)
    _Appl_PvrList = TryResolve("_Z12Appl_PvrListjj");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_PvrList;
}
