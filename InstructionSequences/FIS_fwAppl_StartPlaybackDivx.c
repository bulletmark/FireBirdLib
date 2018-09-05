#include "libFireBird.h"

inline dword FIS_fwAppl_StartPlaybackDivx(void)
{
  TRACEENTER;

  static dword          fwAppl_StartPlaybackDivx = 0;

  if(!fwAppl_StartPlaybackDivx)
    fwAppl_StartPlaybackDivx = TryResolve("_Z22Appl_StartPlaybackDivxPcjb");

  TRACEEXIT;
  return fwAppl_StartPlaybackDivx;
}
