#include "../libFireBird.h"

inline dword FIS_vTimerTempInfo(void)
{
  TRACEENTER();

  static dword          vtimerTempInfo = 0;

  if(!vtimerTempInfo)
    vtimerTempInfo = TryResolve("_timerTempInfo");

  TRACEEXIT();
  return vtimerTempInfo;
}
