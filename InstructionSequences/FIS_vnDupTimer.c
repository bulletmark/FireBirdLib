#include "../libFireBird.h"

inline dword FIS_vnDupTimer(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vnDupTimer");
  #endif

  static dword          vnDupTimer = 0;

  if(!vnDupTimer) vnDupTimer = TryResolve("_nDupTimer");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vnDupTimer;
}
