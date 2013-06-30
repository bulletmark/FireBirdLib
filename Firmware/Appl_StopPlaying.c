#include                "../libFireBird.h"

dword Appl_StopPlaying(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_StopPlaying");
  #endif

  dword                 (*__Appl_StopPlaying)(void);
  dword                 ret = 0;

  __Appl_StopPlaying = (void*)FIS_fwAppl_StopPlaying();
  if(__Appl_StopPlaying) ret = __Appl_StopPlaying();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
