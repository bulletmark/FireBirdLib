#include "../libFireBird.h"

inline dword FIS_vIsPipActive(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vIsPipActive");
  #endif

  static dword          _isPipActive = 0;

  if(!_isPipActive)
    _isPipActive = TryResolve("_isPipActive");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _isPipActive;
}
