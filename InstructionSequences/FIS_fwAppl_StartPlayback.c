#include "../libFireBird.h"

inline dword FIS_fwAppl_StartPlayback(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_StartPlayback");
  #endif

  static dword          fwAppl_StartPlayback = 0;

  if(!fwAppl_StartPlayback)
    fwAppl_StartPlayback = TryResolve("_Z18Appl_StartPlaybackPKcjb");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwAppl_StartPlayback;
}
