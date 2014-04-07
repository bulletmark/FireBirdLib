#include "../libFireBird.h"

inline dword FIS_vCurTapTask(void)
{
  TRACEENTER();

  static dword          vcurTapTask = 0;

  if(!vcurTapTask)
    vcurTapTask = TryResolve("_curTapTask");

  TRACEEXIT();
  return vcurTapTask;
}
