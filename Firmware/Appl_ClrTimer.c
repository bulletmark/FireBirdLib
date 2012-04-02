#include                "../libFireBird.h"

void Appl_ClrTimer(byte *TimerHandle)
{
  void                  (*__Appl_ClrTimer)(byte*);

  __Appl_ClrTimer = (void*)FIS_fwAppl_ClrTimer();
  if(__Appl_ClrTimer) __Appl_ClrTimer(TimerHandle);
}
