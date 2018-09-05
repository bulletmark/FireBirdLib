#include "libFireBird.h"

inline dword FIS_vFlashBlockTimer(void)
{
  TRACEENTER;

  static dword          *vFlashTimer = 0;

  if(!vFlashTimer)
    vFlashTimer = (dword*)TryResolve("_timer");

  TRACEEXIT;
  return (vFlashTimer ? *vFlashTimer : 0);
}
