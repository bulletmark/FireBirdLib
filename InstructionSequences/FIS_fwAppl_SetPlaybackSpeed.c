#include "../libFireBird.h"

inline dword FIS_fwAppl_SetPlaybackSpeed(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_SetPlaybackSpeed");
  #endif

  static dword          _Appl_SetPlaybackSpeed = 0;

  if(!_Appl_SetPlaybackSpeed)
    _Appl_SetPlaybackSpeed = TryResolve("_Z21Appl_SetPlaybackSpeedhib");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_SetPlaybackSpeed;
}
