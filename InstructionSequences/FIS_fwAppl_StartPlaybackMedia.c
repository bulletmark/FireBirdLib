#include "../libFireBird.h"

inline dword FIS_fwAppl_StartPlaybackMedia(void)
{
  static dword          fwAppl_StartPlaybackMedia = 0;

  if (!fwAppl_StartPlaybackMedia)
    fwAppl_StartPlaybackMedia = TryResolve("_Z23Appl_StartPlaybackMediaPKcjbb");

  return fwAppl_StartPlaybackMedia;
}
