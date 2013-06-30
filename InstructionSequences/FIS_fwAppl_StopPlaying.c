#include "../libFireBird.h"

inline dword FIS_fwAppl_StopPlaying(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_StopPlaying");
  #endif

  static dword          _Appl_StopPlaying = 0;

  if(!_Appl_StopPlaying)
    _Appl_StopPlaying = TryResolve("_Z16Appl_StopPlayingv");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _Appl_StopPlaying;
}
