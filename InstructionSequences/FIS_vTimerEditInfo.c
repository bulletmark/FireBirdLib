#include "libFireBird.h"

inline dword FIS_vTimerEditInfo(void)
{
  TRACEENTER();

  static dword          vtimerEditInfo = 0;

  if(!vtimerEditInfo)
    vtimerEditInfo = TryResolve("_timerEditInfo");

  TRACEEXIT();
  return vtimerEditInfo;
}
