#include "../libFireBird.h"

inline dword FIS_vTimerTempInfo(void)
{
  static dword          vtimerTempInfo = 0;

  if(!vtimerTempInfo)
  {
    vtimerTempInfo = TryResolve("_timerTempInfo");
  }

  return vtimerTempInfo;
}
