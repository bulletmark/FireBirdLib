#include                "../libFireBird.h"

void Appl_StopRecPlaying(bool p1)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_StopRecPlaying");
  #endif

  void(*__Appl_StopRecPlaying)(bool);

  __Appl_StopRecPlaying = (void*)FIS_fwAppl_StopPlaying();
  if(__Appl_StopRecPlaying) __Appl_StopRecPlaying(p1);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
