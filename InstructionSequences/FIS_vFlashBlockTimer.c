#include "../libFireBird.h"

inline dword FIS_vFlashBlockTimer(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockTimer");
  #endif

  static dword          *vFlashTimer = 0;

  if(!vFlashTimer)
    vFlashTimer = (dword*)TryResolve("_timer");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashTimer ? *vFlashTimer : 0);
}
