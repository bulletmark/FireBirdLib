#include "../libFireBird.h"

inline dword FIS_fwAppl_StartPlaybackMedia(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_StartPlaybackMedia");
  #endif

  static dword          fwAppl_StartPlaybackMedia = 0;

  if(!fwAppl_StartPlaybackMedia)
    fwAppl_StartPlaybackMedia = TryResolve("_Z23Appl_StartPlaybackMediaPKcjbb");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwAppl_StartPlaybackMedia;
}
