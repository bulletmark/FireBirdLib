#include "../libFireBird.h"

inline dword FIS_vPipW(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vPipW");
  #endif

  static dword          _pipW = 0;

  if(!_pipW)
    _pipW = TryResolve("_pipW");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _pipW;
}
