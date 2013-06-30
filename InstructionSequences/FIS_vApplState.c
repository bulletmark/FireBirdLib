#include "../libFireBird.h"

inline dword FIS_vApplState(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vApplState");
  #endif

  static dword          vapplState = 0;

  if(!vapplState)
    vapplState = TryResolve("_applState");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vapplState;
}
