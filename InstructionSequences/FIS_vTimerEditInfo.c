#include "../libFireBird.h"

inline dword FIS_vTimerEditInfo(void)
{
  static dword          vtimerEditInfo = 0;

  if(!vtimerEditInfo)
  {
    vtimerEditInfo = TryResolve("_timerEditInfo");
  }

  return vtimerEditInfo;
}
