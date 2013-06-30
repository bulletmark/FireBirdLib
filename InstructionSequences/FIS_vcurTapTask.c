#include "../libFireBird.h"

inline dword FIS_vCurTapTask(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vCurTapTask");
  #endif

  static dword          vcurTapTask = 0;

  if(!vcurTapTask)
    vcurTapTask = TryResolve("_curTapTask");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vcurTapTask;
}
