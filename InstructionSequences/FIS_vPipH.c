#include "../libFireBird.h"

inline dword FIS_vPipH(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vPipH");
  #endif

  static dword          _pipH = 0;

  if(!_pipH)
    _pipH = TryResolve("_pipH");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _pipH;
}
