#include "../libFireBird.h"

inline dword FIS_vPipX(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vPipX");
  #endif

  static dword          _pipX = 0;

  if(!_pipX)
    _pipX = TryResolve("_pipX");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _pipX;
}
