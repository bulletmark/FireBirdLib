#include "../libFireBird.h"

inline dword FIS_fwAppl_StopRecPlaying(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwAppl_StopRecPlaying");
  #endif

  static dword          fwAppl_StopRecPlaying = 0;

  if(!fwAppl_StopRecPlaying)
    fwAppl_StopRecPlaying = TryResolve("_Z19Appl_StopRecPlayingb");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return fwAppl_StopRecPlaying;
}
