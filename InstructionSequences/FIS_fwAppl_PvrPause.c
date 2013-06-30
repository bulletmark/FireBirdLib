#include "../libFireBird.h"

inline dword FIS_fwAppl_PvrPause(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_PvrPause");
  #endif

  static dword          _Appl_PvrPause = 0;

  if(!_Appl_PvrPause)
    _Appl_PvrPause = TryResolve("_Z13Appl_PvrPauseb");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_PvrPause;
}
