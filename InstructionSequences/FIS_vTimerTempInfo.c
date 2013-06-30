#include "../libFireBird.h"

inline dword FIS_vTimerTempInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vTimerTempInfo");
  #endif

  static dword          vtimerTempInfo = 0;

  if(!vtimerTempInfo)
    vtimerTempInfo = TryResolve("_timerTempInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vtimerTempInfo;
}
