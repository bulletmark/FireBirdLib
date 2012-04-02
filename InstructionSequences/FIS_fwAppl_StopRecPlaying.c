#include "../libFireBird.h"

inline dword FIS_fwAppl_StopRecPlaying(void)
{
  static dword          fwAppl_StopRecPlaying = 0;

  if (!fwAppl_StopRecPlaying)
    fwAppl_StopRecPlaying = TryResolve("_Z19Appl_StopRecPlayingb");

  return fwAppl_StopRecPlaying;
}
