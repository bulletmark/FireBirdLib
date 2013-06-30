#include "../libFireBird.h"

inline dword FIS_vTimerEditInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vTimerEditInfo");
  #endif

  static dword          vtimerEditInfo = 0;

  if(!vtimerEditInfo)
    vtimerEditInfo = TryResolve("_timerEditInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vtimerEditInfo;
}
