#include "../libFireBird.h"

inline dword FIS_vPipY(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vPipY");
  #endif

  static dword          _pipY = 0;

  if(!_pipY)
    _pipY = TryResolve("_pipY");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _pipY;
}
