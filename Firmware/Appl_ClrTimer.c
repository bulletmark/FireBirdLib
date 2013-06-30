#include                "../libFireBird.h"

void Appl_ClrTimer(byte *TimerHandle)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_ClrTimer");
  #endif

  void                  (*__Appl_ClrTimer)(byte*);

  __Appl_ClrTimer = (void*)FIS_fwAppl_ClrTimer();
  if(__Appl_ClrTimer) __Appl_ClrTimer(TimerHandle);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
