#include "../libFireBird.h"

inline dword FIS_fwAppl_StartPlaybackMp3(void)
{
  TRACEENTER();

  static dword          fwAppl_StartPlaybackMp3 = 0;

  if(!fwAppl_StartPlaybackMp3)
    fwAppl_StartPlaybackMp3 = TryResolve("_Z21Appl_StartPlaybackMp3PKc");

  TRACEEXIT();
  return fwAppl_StartPlaybackMp3;
}
