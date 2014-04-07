#include "../libFireBird.h"

inline dword FIS_fwAppl_StartPlayback(void)
{
  TRACEENTER();

  static dword          fwAppl_StartPlayback = 0;

  if(!fwAppl_StartPlayback)
    fwAppl_StartPlayback = TryResolve("_Z18Appl_StartPlaybackPKcjb");

  TRACEEXIT();
  return fwAppl_StartPlayback;
}
