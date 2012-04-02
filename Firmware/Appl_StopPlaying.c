#include                "../libFireBird.h"

dword Appl_StopPlaying(void)
{
  dword                 (*__Appl_StopPlaying)(void);
  dword                 ret = 0;

  __Appl_StopPlaying = (void*)FIS_fwAppl_StopPlaying();
  if(__Appl_StopPlaying) ret = __Appl_StopPlaying();

  return ret;
}
